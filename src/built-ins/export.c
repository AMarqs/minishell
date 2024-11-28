/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:09:30 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/28 12:42:27 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	add_one_envp(t_env *tmp, t_env *new)
{
	t_env	*prev;

	while (tmp)
	{
		if ((ft_strcmp(tmp->key, new->key)) == 0)
		{
			if (!new->value)
				return ;
			if (tmp->value)
				free(tmp->value);
			free(new->key);
			tmp->value = new->value;
			free(new);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	if (!tmp)
		prev->next = new;
}

void	add_envp(t_shell *shell, t_env *new)
{
	t_env	*tmp;

	tmp = shell->envp;
	if (!shell->envp)
	{
		shell->envp = new;
		return ;
	}
	add_one_envp(tmp, new);
}

int	check_export(char *args)
{
	int	i;

	i = 1;
	if (!ft_isalpha(args[0]) && args[0] != '_')
		return (0);
	while (args[i] && args[i] != '=')
	{
		if (args[i] == '+' && args[i + 1] != '=')
			return (0);
		if (!ft_isalnum(args[i]) && args[i] != '_' && args[i] != '+')
			return (0);
		i++;
	}
	return (1);
}

int	export(t_shell *shell, char **args)
{
	t_env	*new;
	int		i;

	i = -1;
	if (!args || args[0] == NULL)
	{
		if (shell->envp)
			return (order_env(shell));
		return (1);
	}
	while (args[++i])
	{
		if (check_export(args[i]))
		{
			new = malloc(sizeof(t_env));
			if (!new)
				return (0);
			ft_split_var(shell, new, args[i]);
			new->next = NULL;
			add_envp(shell, new);
		}
		else
			export_error(shell, args[i]);
	}
	return (1);
}
