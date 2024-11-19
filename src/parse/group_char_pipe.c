/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_char_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:40:19 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/19 14:41:04 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*group_chars(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;
	char	*str;
	char	*str2;
	char	aux[2];
	char	*aux2;
	int		is_var;

	tmp = tokens;
	str = NULL;
	is_var = 0;
	while (tmp && (tmp->type == CHAR || tmp->type == ENV_VAR
			|| tmp->type == ENV_VAR_Q || tmp->type == EMPTY))
	{
		while (tmp && tmp->type == CHAR)
		{
			aux[0] = tmp->value;
			aux[1] = '\0';
			str2 = better_strjoin(str, aux);
			if (!str2)
			{
				free(str);
				free_all_malloc(shell);
			}
			free(str);
			str = str2;
			tmp = tmp->next;
		}
		if (tmp && tmp->type == ENV_VAR_Q)
		{
			aux2 = subs_var(shell, &tmp, str);
			if (aux2)
			{
				str2 = better_strjoin(str, aux2);
				free(aux2);
				if (!str2)
				{
					free(str);
					free_all_malloc(shell);
				}
				free(str);
				str = str2;
			}
		}
		if (tmp && tmp->type == ENV_VAR)
		{
			aux2 = subs_var(shell, &tmp, str);
			if (aux2)
				str = space_split(shell, str, aux2, &is_var);
			free(aux2);
		}
		if (tmp && tmp->type == EMPTY)
		{
			str2 = better_strjoin(str, "");
			free(str);
			if (!str2)
				free_all_malloc(shell);
			str = str2;
			tmp = tmp->next;
		}
	}
	tokens = tmp;
	if (!str)
		return (tokens);
	if (!add_args_group(shell, str, is_var))
	{
		free(str);
		free_all_malloc(shell);
	}
	return (tokens);
}

t_token	*group_pipe(t_shell *shell, t_token *tokens)
{
	t_group	*new;
	t_token	*tmp;
	int		i;

	new = new_group();
	if (!new)
		free_all_malloc(shell);
	add_group(shell, new);
	tmp = tokens;
	i = 0;
	tmp = tmp->next;
	while (tmp && tmp->type != CHAR_PIPE)
	{
		tmp = tmp->next;
		i++;
	}
	tmp = tokens->next;
	while (tmp && tmp->type == BLANK)
	{
		tmp = tmp->next;
		i--;
	}
	if (i == 0)
	{
		shell->exit_status = 2;
		new->type = PIPE;
		new->word = ft_strdup("|");
		if (!new->word)
			free_all_malloc(shell);
	}
	else
	{
		new->type = PIPE;
		new->word = ft_strdup("|");
		if (!new->word)
			free_all_malloc(shell);
	}
	tokens = tmp;
	return (tokens);
}
