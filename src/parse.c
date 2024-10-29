/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:41:05 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/29 20:00:31 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*new_token(enum e_token type, char value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL); /////////////////////// ADD ERROR FUNCTION
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void add_token(t_shell *shell, t_token *new)
{
	t_token	*tmp;

	tmp = shell->tokens;
	if (!shell->tokens)
	{
		shell->tokens = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	create_token(t_shell *shell, enum e_token type, char value)
{
	t_token	*new;

	new = new_token(type, value);
	add_token(shell, new);
}

int	token_type(char c)
{
	if (!c)
		return (NULLCHAR);
	if (c == '|')
		return (CHAR_PIPE);
	if (c == '<')
		return (CHAR_IN);
	if (c == '>')
		return (CHAR_OUT);
	if (c == '\'')
		return (S_QUOTE);
	if (c == '"')
		return (D_QUOTE);
	if (c == '$')
		return (ENV_VAR);
	if (c == ' ')
		return (BLANK);
	return (CHAR);
}

int	is_closed_quotes(int type, char *line, int i)
{
	int		closed;

	closed = 0;
	while (line[i])
	{
		if (token_type(line[i]) == type)
		{
			closed = 1;
			break ;
		}
		i++;
	}
	return (closed);
}

int	tokenize_quotes(t_shell *shell, int type, int j)
{
	int i;
	char *line;

	line = shell->line;
	i = j;
	while (token_type(line[i]) != type)
	{
		if (token_type(line[i]) == ENV_VAR && type == D_QUOTE)
		{
			if (line[i + 1] == '?')
			{
				create_token(shell, ENV_VAR, line[++i]);
			}
			else if (line[i + 1] == '_' || ft_isalpha(line[i + 1]))
			{
				while (ft_isalnum(line[++i]) || line[i] == '_')
				{
					create_token(shell, ENV_VAR, line[i]);
				}
				i--;
			}
			else
				create_token(shell, CHAR, line[i]);
		}
		else
			create_token(shell, CHAR, line[i]);
		i++;
	}
	return (i);
}

void	parse_line(t_shell *shell)
{
	char	*line;
	int		i;
	int		closed;
	int		type;

	i = 0;
	line = shell->line;
	shell->tokens = NULL;
	while (line[i])
	{
		type = token_type(line[i]);
		if (type == S_QUOTE || type == D_QUOTE)
		{
			closed = is_closed_quotes(type, line, i + 1);
			if (!closed)
				create_token(shell, CHAR, line[i]);
			else
				i = tokenize_quotes(shell, type, i + 1);
		}
		else if (type == ENV_VAR)
		{
			if (line[i + 1] == '?')
			{
				create_token(shell, ENV_VAR, line[++i]);
			}
			else if (line[i + 1] == '_' || ft_isalpha(line[i + 1]))
			{
				while (ft_isalnum(line[++i]) || line[i] == '_')
				{
					create_token(shell, ENV_VAR, line[i]);
				}
				i--;
			}
			else
				create_token(shell, CHAR, line[i]);
		}
		else
			create_token(shell, type, line[i]);
		i++;
	}
}