/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:37:11 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/20 21:47:44 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_subs_env(char **array, char *str, int j, int k)
{
	array[0] = ft_substr(str, 0, k);
	if (!array[0])
	{
		free(array);
		return (NULL);
	}
	if (j)
	{
		array[1] = ft_substr(str, k + 1, j);
		if (!array[1])
		{
			free(array[0]);
			free(array);
			return (NULL);
		}
		array[2] = NULL;
	}
	else
		array[1] = NULL;
	return (array);
}

char	**ft_split_env(char *str, char del)
{
	char	**array;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (str[i] && str[i] != del)
		i++;
	k = i;
	if (str[i] == del)
		i++;
	while (str[i++])
		j++;
	if (j)
		array = malloc(sizeof(char *) * (3));
	else
		array = malloc(sizeof(char *) * (2));
	if (!array)
		return (NULL);
	array = ft_subs_env(array, str, j, k);
	if (!array)
		return (NULL);
	return (array);
}

void	fill_envp(t_shell *shell, char **env, t_env *tmp)
{
	char	*tmp2;
	int		i;

	i = 0;
	while (tmp)
	{
		if (tmp->value)
		{
			tmp2 = ft_strjoin(tmp->key, "=");
			env[i] = ft_strjoin(tmp2, tmp->value);
			free(tmp2);
		}
		else
			env[i] = ft_strdup(tmp->key);
		if (!env[i])
		{
			while (--i >= 0)
				free(env[i]);
			free(env);
			free_all_malloc(shell);
		}
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
}

char	**get_envp(t_shell *shell)
{
	t_env	*tmp;
	char	**env;
	int		i;

	tmp = shell->envp;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		free_all_malloc(shell);
	tmp = shell->envp;
	fill_envp(shell, env, tmp);
	return (env);
}

void	free_envp(char **env, char *cmd)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	free(cmd);
}
