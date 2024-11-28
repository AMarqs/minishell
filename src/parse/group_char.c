/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:40:19 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/28 18:13:47 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*group_chars_char(t_shell *shell, t_token **tmp, char *str)
{
	char	aux[2];
	char	*str2;

	aux[0] = (*tmp)->value;
	aux[1] = '\0';
	str2 = better_strjoin(str, aux);
	if (!str2)
	{
		free(str);
		free_all_malloc(shell);
	}
	free(str);
	str = str2;
	*tmp = (*tmp)->next;
	return (str);
}

char	*group_chars_var_q(t_shell *shell, t_token **tmp, char *str)
{
	char	*aux;
	char	*str2;

	aux = subs_var(shell, tmp, str);
	if (aux)
	{
		str2 = better_strjoin(str, aux);
		free(aux);
		free(str);
		if (!str2)
			free_all_malloc(shell);
		str = str2;
	}
	return (str);
}

char	*group_chars_var(t_shell *shell, t_token **tmp, char *str, int *is_var)
{
	char	*aux;

	aux = subs_var(shell, tmp, str);
	if (aux)
		str = space_split(shell, str, aux, is_var);
	free(aux);
	return (str);
}

char	*group_chars_empty(t_shell *shell, t_token **tmp, char *str)
{
	char	*aux;

	aux = better_strjoin(str, "");
	free(str);
	if (!aux)
		free_all_malloc(shell);
	str = aux;
	*tmp = (*tmp)->next;
	return (str);
}

t_token	*group_chars(t_shell *shell, t_token *tokens)
{
	char	*str;
	int		is_var;

	str = NULL;
	is_var = 0;
	while (tokens && (tokens->type == CHAR || tokens->type == ENV_VAR
			|| tokens->type == ENV_VAR_Q || tokens->type == EMPTY))
	{
		while (tokens && tokens->type == CHAR)
			str = group_chars_char(shell, &tokens, str);
		if (tokens && (tokens->type == ENV_VAR || tokens->type == ENV_VAR_Q))
		{
			if (is_delimeter(shell))
				str = subs_delimiter(shell, &tokens, str);
			else if (tokens && tokens->type == ENV_VAR_Q)
				str = group_chars_var_q(shell, &tokens, str);
			else if (tokens && tokens->type == ENV_VAR)
				str = group_chars_var(shell, &tokens, str, &is_var);
		}
		if (tokens && tokens->type == EMPTY)
			str = group_chars_empty(shell, &tokens, str);
	}
	if (!add_args_group(shell, str, is_var))
		free_all_malloc(shell);
	return (tokens);
}
