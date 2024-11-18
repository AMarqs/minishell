/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:09:20 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/18 20:22:37 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unset_node(t_shell *shell, char *arg)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = shell->envp;
	prev = NULL;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, arg) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				shell->envp = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	unset(t_shell *shell, char **args)
{
	int		i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		unset_node(shell, args[i]);
		i++;
	}
}
