/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:09:20 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/08 18:26:36 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	unset(t_shell *shell, char **args)
{
	t_env	*tmp;
	t_env	*prev;
	int		i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		tmp = shell->envp;
		prev = NULL;
		while (tmp)
		{
			if (ft_strcmp(tmp->key, args[i]) == 0)
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
		i++;
	}
}
