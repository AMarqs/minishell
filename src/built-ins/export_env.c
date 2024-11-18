/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:34:56 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/18 20:15:58 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	node_dup(t_env **envp, t_env *new, t_env **tmp, t_env **tmp2)
{
	new->key = (*envp)->key;
	new->value = (*envp)->value;
	new->next = NULL;
	if (!(*tmp))
	{
		*tmp = new;
		*tmp2 = *tmp;
	}
	else
	{
		(*tmp)->next = new;
		*tmp = (*tmp)->next;
	}
	(*envp) = (*envp)->next;
}

t_env	*envp_dup(t_env *envp)
{
	t_env	*new;
	t_env	*tmp;
	t_env	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	while (envp)
	{
		new = malloc(sizeof(t_env));
		if (!new)
		{
			while (tmp2)
			{
				tmp = tmp2;
				tmp2 = tmp2->next;
				free(tmp);
			}
			return (NULL);
		}
		node_dup(&envp, new, &tmp, &tmp2);
	}
	return (tmp2);
}

void	order_dup(t_env *sorted, t_env *first, int len)
{
	t_env	*tmp;

	while (sorted)
	{
		len++;
		sorted = sorted->next;
	}
	while (len--)
	{
		sorted = first;
		while (sorted)
		{
			tmp = sorted->next;
			while (tmp)
			{
				if (ft_strcmp(sorted->key, tmp->key) > 0)
				{
					ft_swap(&sorted->key, &tmp->key);
					ft_swap(&sorted->value, &tmp->value);
				}
				tmp = tmp->next;
			}
			sorted = sorted->next;
		}
	}
}

void	print_node(t_env *tmp)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(tmp->key, 1);
	if (tmp->value)
	{
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(tmp->value, 1);
		ft_putstr_fd("\"", 1);
	}
	ft_putstr_fd("\n", 1);
}

int	order_env(t_shell *shell)
{
	t_env	*tmp;
	t_env	*sorted;
	t_env	*first;
	int		len;

	len = 0;
	sorted = envp_dup(shell->envp);
	if (!sorted)
		return (0);
	first = sorted;
	order_dup(sorted, first, len);
	tmp = first;
	while (tmp)
	{
		print_node(tmp);
		tmp = tmp->next;
	}
	sorted = first;
	while (sorted)
	{
		tmp = sorted;
		sorted = sorted->next;
		free(tmp);
	}
	return (1);
}
