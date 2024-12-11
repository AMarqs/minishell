/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:10:28 by glopez-c          #+#    #+#             */
/*   Updated: 2024/12/11 12:18:49 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"	

t_token	*group_pipe(t_shell *shell, t_token *tokens)
{
	t_group	*new;

	new = new_group();
	if (!new)
		free_all_malloc(shell);
	add_group(shell, new);
	new->type = PIPE;
	new->word = ft_strdup("|");
	if (!new->word)
		free_all_malloc(shell);
	tokens = tokens->next;
	return (tokens);
}

int	syntax_check_loop(t_shell *shell, t_group *tmp, t_group *next)
{
	if (tmp->type == REDIR_APPEND || tmp->type == REDIR_HD
		|| tmp->type == REDIR_IN || tmp->type == REDIR_OUT)
	{
		if (!next)
			syntax_error_newline(shell);
		else if (next->type != ARG)
			syntax_error(shell, next->word);
		else if (next->is_var && next->next && next->next->is_var)
			ambiguous_error(shell, tmp);
		if ((!next) || (next->type != ARG) || (next->is_var
				&& next->next && next->next->is_var))
			return (0);
		else
			next->type = FILENAME;
	}
	else if (tmp->type == PIPE)
	{
		if (!next)
			syntax_error_newline(shell);
		else if (next->type == PIPE)
			syntax_error(shell, next->word);
		if ((!next) || (next->type == PIPE))
			return (0);
	}
	return (1);
}

void	syntax_check(t_shell *shell)
{
	t_group	*tmp;

	tmp = shell->groups;
	if (tmp->type == PIPE)
	{
		syntax_error(shell, "|");
		return ;
	}
	while (tmp)
	{
		if (!syntax_check_loop(shell, tmp, tmp->next))
			break ;
		tmp = tmp->next;
	}
}

void	find_cmds(t_shell *shell)
{
	t_group	*tmp;
	int		is_cmd;

	tmp = shell->groups;
	is_cmd = 1;
	while (tmp)
	{
		if (tmp->type == ARG)
		{
			if (is_cmd)
			{
				tmp->type = CMD;
				is_cmd = 0;
			}
		}
		else if (tmp->type == PIPE)
			is_cmd = 1;
		tmp = tmp->next;
	}
}

void	group_tokens(t_shell *shell)
{
	t_token	*tokens;

	tokens = shell->tokens;
	while (tokens)
	{
		if (tokens->type == BLANK)
			while (tokens && tokens->type == BLANK)
				tokens = tokens->next;
		else if (tokens->type == CHAR || tokens->type == ENV_VAR
			|| tokens->type == ENV_VAR_Q || tokens->type == EMPTY)
			tokens = group_chars(shell, tokens);
		else if (tokens->type == CHAR_PIPE)
			tokens = group_pipe(shell, tokens);
		else if (tokens->type == CHAR_IN)
			tokens = group_in(shell, tokens);
		else if (tokens->type == CHAR_OUT)
			tokens = group_out(shell, tokens);
	}
	if (shell->groups)
	{
		syntax_check(shell);
		find_cmds(shell);
	}
}
