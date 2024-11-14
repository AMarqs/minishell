/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:09:30 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/14 13:52:59 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
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
		new->key = envp->key;
		new->value = envp->value;
		new->next = NULL;
		if (!tmp)
		{
			tmp = new;
			tmp2 = tmp;
		}
		else
		{
			tmp->next = new;
			tmp = tmp->next;
		}
		envp = envp->next;
	}
	return (tmp2);
}

int	order_env(t_shell *shell)
{
	t_env	*tmp;
	t_env	*sorted;
	t_env	*first;
	int 	len;

	len = 0;
	sorted = envp_dup(shell->envp);
	if (!sorted)
		return (0);
	first = sorted;
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
	tmp = first;
	while (tmp)
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

void	ft_split_var(t_env *new, char *value)
{
	char	**tmp;

	tmp = ft_split_env(value, '=');
	new->key = tmp[0];
	if (!tmp[1] && value[ft_strlen(value) - 1] == '=')
		new->value = ft_strdup("");
	else
		new->value = tmp[1];
	free(tmp);
}

void	add_envp(t_shell *shell, t_env *new)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = shell->envp;
	if (!shell->envp)
	{
		shell->envp = new;
		return ;
	}
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

int	check_export(char *args)
{
	int	i;

	i = 1;
	if (!ft_isalpha(args[0]) && args[0] != '_')
		return (0);
	while (args[i] && args[i] != '=')
	{
		if (!ft_isalnum(args[i]) && args[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	export(t_shell *shell, char **args)
{
	t_env	*new;
	int		i;

	i = 0;
	shell->exit_status = 0;
	if (!args || args[0] == NULL)
	{
		if (shell->envp)
			if (!order_env(shell))
				return (0);
		return (1);
	}
	while (args[i])
	{
		if (check_export(args[i]))
		{
			new = malloc(sizeof(t_env));
			if (!new)
					return (0);
			ft_split_var(new, args[i]); 
			new->next = NULL;
			add_envp(shell, new);
		}
		else
		{
			shell->exit_status = 1;
			write(2, "minishell: export: `", 20);
			write(2, args[i], ft_strlen(args[i]));
			write(2, "': not a valid identifier\n", 26);
		}
		i++;
	}
	return (1);
}
