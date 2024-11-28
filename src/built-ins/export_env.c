/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:34:56 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/28 21:53:13 by glopez-c         ###   ########.fr       */
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

void	add_nl(t_shell *shell, char **args, char *str)
{
	char	*aux;

	aux = ft_strjoin(str, "\n");
	free(str);
	if (!aux)
		free_builtin(shell, args);
	ft_putstr_fd(aux, 1);
	free(aux);
}

void	print_node(t_shell *shell, char **args, t_env *tmp)
{
	char	*str;
	char	*aux;

	str = ft_strjoin("declare -x ", tmp->key);
	if (!str)
		free_builtin(shell, args);
	if (tmp->value)
	{
		aux = ft_strjoin(str, "=\"");
		free(str);
		if (!aux)
			free_builtin(shell, args);
		str = ft_strjoin(aux, tmp->value);
		free(aux);
		if (!str)
			free_builtin(shell, args);
		aux = ft_strjoin(str, "\"");
		free(str);
		if (!aux)
			free_builtin(shell, args);
		str = aux;
	}
	add_nl(shell, args, str);
}
