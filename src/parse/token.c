/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:00:53 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/19 14:02:25 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (c == ' ' || c == '\t')
		return (BLANK);
	return (CHAR);
}

t_token	*new_token(enum e_token type, char value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

void	add_token(t_shell *shell, t_token *new)
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

t_token	*create_token(t_shell *shell, enum e_token type, char value)
{
	t_token	*new;

	new = new_token(type, value);
	if (!new)
	{
		free_all(shell);
		malloc_error();
	}
	add_token(shell, new);
	return (new);
}
