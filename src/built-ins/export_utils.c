/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:27:26 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/28 12:55:29 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	export_error(t_shell *shell, char *arg)
{
	write(2, "minishell: export: `", 20);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 26);
	shell->exit_status = 1;
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

void	concatenate_export(t_shell *shell, t_env *new, char **split)
{
	new->key = ft_substr(split[0], 0, ft_strlen(split[0]) - 1);
	free(split[0]);
	if (!new->key)
	{
		free(new);
		free(split[1]);
		free(split);
		free_all_malloc(shell);
	}
	if (!search_env(shell, new->key))
		new->value = split[1];
	else
	{
		new->value = ft_strjoin(search_env(shell, new->key), split[1]);
		free(split[1]);
		if (!new->value)
		{
			free(new->key);
			free(new);
			free(split);
			free_all_malloc(shell);
		}
	}
}

void	ft_split_var(t_shell *shell, t_env *new, char *value)
{
	char	**tmp;

	tmp = ft_split_env(value, '=');
	if (!tmp)
	{
		free(new);
		free_all_malloc(shell);
	}
	if (ft_strchr(tmp[0], '+'))
		concatenate_export(shell, new, tmp);
	else
	{
		new->key = tmp[0];
		if (!tmp[1] && value[ft_strlen(value) - 1] == '=')
			new->value = ft_strdup("");
		else
			new->value = tmp[1];
	}
	free(tmp);
}
