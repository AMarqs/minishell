/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:18:31 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/15 18:24:43 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	malloc_error(void)
{
	ft_putstr_fd("Fatal error: malloc: memory allocation error\n", 2);
	exit(1);
}

void	free_heredocs(t_shell *shell)
{
	t_group	*tmp;

	tmp = shell->groups;
	while (tmp)
	{
		if (tmp->type == REDIR_HD)
		{
			if (tmp->file)
			{
				unlink(tmp->file);
				free(tmp->file);
			}
		}
		tmp = tmp->next;
	}
}

void	*free_groups(t_group *group)
{
	t_group	*tmp;

	while (group)
	{
		tmp = group->next;
		free(group->word);
		free(group);
		group = tmp;
	}
	return (NULL);
}

void	*free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token);
		token = tmp;
	}
	return (NULL);
}

void	free_all(t_shell *shell)
{
	t_env	*tmp;
	t_env	*aux;

	free_heredocs(shell);
	tmp = shell->envp;
	while (tmp)
	{
		aux = tmp->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
		tmp = aux;
	}
	free(shell->line);
	free(shell->path);
	free_tokens(shell->tokens);
	free_groups(shell->groups);
	free(shell);
	rl_clear_history();
}
