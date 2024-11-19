/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:41:05 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/19 14:19:32 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

int	double_quotes(t_shell *shell, char *line, int i)
{
	t_token	*new;

	new = create_token(shell, ENV_VAR_Q, line[i]);
	if (line[i + 1] == '?')
		create_token(shell, ENV_VAR, line[++i]);
	else if (line[i + 1] == '_' || ft_isalpha(line[i + 1]))
	{
		while (ft_isalnum(line[++i]) || line[i] == '_')
			create_token(shell, ENV_VAR_Q, line[i]);
		i--;
	}
	else
		new->type = CHAR;
	return (i);
}

int	tokenize_quotes(t_shell *shell, int type, int j)
{
	int		i;
	char	*line;

	line = shell->line;
	i = j;
	while (token_type(line[i]) != type)
	{
		if (token_type(line[i]) == ENV_VAR && type == D_QUOTE)
			i = double_quotes(shell, line, i);
		else
			create_token(shell, CHAR, line[i]);
		i++;
	}
	if (i == j)
		create_token(shell, EMPTY, '\0');
	return (i);
}

int	token_var(t_shell *shell, char *line, int i)
{
	t_token	*new;

	new = create_token(shell, ENV_VAR, line[i]);
	if (line[i + 1] == '?')
		create_token(shell, ENV_VAR, line[++i]);
	else if (line[i + 1] == '_' || ft_isalpha(line[i + 1]))
	{
		while (ft_isalnum(line[++i]) || line[i] == '_')
			create_token(shell, ENV_VAR, line[i]);
		i--;
	}
	else
		new->type = CHAR;
	return (i);
}

void	parse_line(t_shell *shell)
{
	char	*line;
	int		i;
	int		type;

	i = 0;
	line = shell->line;
	while (line[i])
	{
		type = token_type(line[i]);
		if (type == S_QUOTE || type == D_QUOTE)
		{
			if (!is_closed_quotes(type, line, i + 1))
				create_token(shell, CHAR, line[i]);
			else
				i = tokenize_quotes(shell, type, i + 1);
		}
		else if (type == ENV_VAR)
			i = token_var(shell, line, i);
		else
			create_token(shell, type, line[i]);
		i++;
	}
}
