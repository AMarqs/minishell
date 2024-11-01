/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:09:30 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/31 17:20:21 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*envp_dup(t_env *envp)
{
	t_env	*new;
	t_env	*tmp;
	t_env	*tmp2;

	tmp = NULL;
	while (envp)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			return (NULL); /////////////////////// ADD ERROR FUNCTION
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

void	order_env(t_shell *shell)
{
	t_env	*tmp;
	t_env	*sorted;
	t_env	*first;
	int 	len;

	len = 0;
	sorted = envp_dup(shell->envp);
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
		printf("declare -x %s", tmp->key);
		if (tmp->value)
			printf("=\"%s\"", tmp->value);
		printf("\n");
		fflush(stdout);
		tmp = tmp->next;
	}
	sorted = first;
	while (sorted)
	{
		tmp = sorted;
		sorted = sorted->next;
		free(tmp);
	}
}

void	ft_split_env(t_env *new, char *value)
{
	char	**tmp;

	tmp = ft_split(value, '=');
	new->key = tmp[0];
	new->value = tmp[1];
	free(tmp);
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

void	add_envp(t_shell *shell, t_env *new)
{
	t_env	*tmp;

	tmp = shell->envp;
	if (!shell->envp)
	{
		shell->envp = new;
		return ;
	}
	while (tmp->next)
	{
		if ((ft_strcmp(tmp->key, new->key)) == 0)
		{
			free(tmp->value);
			free(new->key);
			tmp->value = new->value;
			free(new);
			return ;
		}
		tmp = tmp->next;
	}
	tmp->next = new;
}

void	export(t_shell *shell, char **args)
{
	t_env	*new;
	int		i;

	i = 0;
	shell->exit_status = 0;
	if (!args)
	{
		order_env(shell);
		return ;
	}
	while (args[i])
	{
		if (check_export(args[i]))
		{
			new = malloc(sizeof(t_env));
			if (!new)
				return ; /////////////////////// ADD ERROR FUNCTION
			ft_split_env(new, args[i]); 
			new->next = NULL;
			add_envp(shell, new);
		}
		else
		{
			shell->exit_status = 1;
			printf("minishell: export: `%s': not a valid identifier\n", args[i]);
			fflush(stdout);
		}
		i++;
	}
}