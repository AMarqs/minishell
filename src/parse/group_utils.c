/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:33:54 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/20 13:57:11 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_group	*new_group(void)
{
	t_group	*group;

	group = malloc(sizeof(t_group));
	if (!group)
		return (NULL);
	group->next = NULL;
	group->word = NULL;
	group->is_var = 0;
	group->file = NULL;
	return (group);
}

void	add_group(t_shell *shell, t_group *new)
{
	t_group	*tmp;

	tmp = shell->groups;
	if (!shell->groups)
	{
		shell->groups = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	add_args_group(t_shell *shell, char *str, int is_var)
{
	t_group	*tmp;
	t_group	*new;

	tmp = shell->groups;
	if (!str)
		return (1);
	new = new_group();
	if (!new)
	{
		free(str);
		return (0);
	}
	new->word = str;
	new->type = ARG;
	new->is_var = is_var;
	if (!shell->groups)
	{
		shell->groups = new;
		return (1);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}
