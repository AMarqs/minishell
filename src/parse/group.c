/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:10:28 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/19 15:03:49 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"	

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
		if (tmp->type == REDIR_APPEND || tmp->type == REDIR_HD
			|| tmp->type == REDIR_IN || tmp->type == REDIR_OUT)
		{
			if (!tmp->next)
			{
				syntax_error_newline(shell);
				break ;
			}
			else if (tmp->next->type != ARG)
			{
				syntax_error(shell, tmp->next->word);
				break ;
			}
			else if (tmp->next->is_var && tmp->next->next
				&& tmp->next->next->is_var)
			{
				ambiguous_error(shell, tmp);
				break ;
			}
			else
				tmp->next->type = FILENAME;
		}
		else if (tmp->type == PIPE)
		{
			if (!tmp->next)
			{
				syntax_error_newline(shell);
				break ;
			}
			else if (tmp->next->type == PIPE)
			{
				syntax_error(shell, tmp->next->word);
				break ;
			}
		}
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
