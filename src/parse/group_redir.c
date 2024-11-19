/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:35:48 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/19 14:36:25 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*group_in(t_shell *shell, t_token *tokens)
{
	t_group	*new;
	t_token	*tmp;
	t_token	*aux;
	int		ok;

	ok = 0;
	tmp = tokens;
	new = new_group();
	if (!new)
		free_all_malloc(shell);
	add_group(shell, new);
	new->type = REDIR_IN;
	new->word = ft_strdup("<"); // se puede quitar ???
	if (!new->word)
		free_all_malloc(shell);
	new->first_token = tmp;
	if (tmp->next && tmp->next->type == CHAR_IN)
	{
		new->type = REDIR_HD;
		free(new->word);
		new->word = ft_strdup("<<"); // se puede quitar ???
		if (!new->word)
			free_all_malloc(shell);
		tmp = tmp->next;
	}
	tmp = tmp->next;
	aux = tmp;
	while (tmp)
	{
		if (tmp->type == CHAR || tmp->type == ENV_VAR || tmp->type == ENV_VAR_Q)
			ok = 1;
		else if (tmp->type != BLANK && ok == 0)
			shell->exit_status = 2;
		tmp = tmp->next;
	}
	tokens = aux;
	return (tokens);
}

t_token	*group_out(t_shell *shell, t_token *tokens)
{
	t_group	*new;
	t_token	*tmp;
	t_token	*aux;
	int		ok;

	ok = 0;
	tmp = tokens;
	new = new_group();
	if (!new)
		free_all_malloc(shell);
	add_group(shell, new);
	new->type = REDIR_OUT;
	new->word = ft_strdup(">"); // se puede quitar
	if (!new->word)
		free_all_malloc(shell);
	new->first_token = tmp;
	if (tmp->next && tmp->next->type == CHAR_OUT)
	{
		new->type = REDIR_APPEND;
		free(new->word);
		new->word = ft_strdup(">>"); // se puede quitar
		if (!new->word)
			free_all_malloc(shell);
		tmp = tmp->next;
	}
	tmp = tmp->next;
	aux = tmp;
	while (tmp)
	{
		if (tmp->type == CHAR || tmp->type == ENV_VAR || tmp->type == ENV_VAR_Q)
			ok = 1;
		else if (tmp->type != BLANK && ok == 0)
			shell->exit_status = 2;
		tmp = tmp->next;
	}
	tokens = aux;
	return (tokens);
}
