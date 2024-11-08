/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 13:18:31 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/08 18:27:02 by glopez-c         ###   ########.fr       */
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

void	free_all(t_shell *shell)
{
	t_env	*tmp;
	t_env	*aux;
	t_token	*tmp1;
	t_token	*aux1;
	t_group	*tmp2;
	t_group	*aux2;

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
	tmp1 = shell->tokens;
	while (tmp1)
	{
		aux1 = tmp1->next;
		free(tmp1);
		tmp1 = aux1;
	}
	tmp2 = shell->groups;
	while (tmp2)
	{
		aux2 = tmp2->next;
		free(tmp2->word);
		free(tmp2);
		tmp2 = aux2;
	}
	free(shell);
}
