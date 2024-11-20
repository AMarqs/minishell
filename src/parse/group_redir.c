/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:35:48 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/20 14:14:08 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*group_in(t_shell *shell, t_token *tokens)
{
	t_group	*new;

	new = new_group();
	if (!new)
		free_all_malloc(shell);
	add_group(shell, new);
	new->type = REDIR_IN;
	new->word = ft_strdup("<");
	if (!new->word)
		free_all_malloc(shell);
	new->first_token = tokens;
	if (tokens->next && tokens->next->type == CHAR_IN)
	{
		new->type = REDIR_HD;
		free(new->word);
		new->word = ft_strdup("<<");
		if (!new->word)
			free_all_malloc(shell);
		tokens = tokens->next;
	}
	tokens = tokens->next;
	return (tokens);
}

t_token	*group_out(t_shell *shell, t_token *tokens)
{
	t_group	*new;

	new = new_group();
	if (!new)
		free_all_malloc(shell);
	add_group(shell, new);
	new->type = REDIR_OUT;
	new->word = ft_strdup(">");
	if (!new->word)
		free_all_malloc(shell);
	new->first_token = tokens;
	if (tokens->next && tokens->next->type == CHAR_OUT)
	{
		new->type = REDIR_APPEND;
		free(new->word);
		new->word = ft_strdup(">>");
		if (!new->word)
			free_all_malloc(shell);
		tokens = tokens->next;
	}
	tokens = tokens->next;
	return (tokens);
}
