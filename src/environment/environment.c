/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:38:45 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/19 13:37:25 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env_value(char **tmp, t_env *new)
{
	if (tmp[1])
		free(tmp[1]);
	free(tmp[0]);
	free(tmp);
	free(new);
}

void	free_environ(t_shell *shell, t_env *tmp, int i)
{
	t_env	*new;

	while (i > 0)
	{
		new = tmp;
		tmp = new->next;
		free(new->key);
		free(new->value);
		free(new);
		i--;
	}
	free_all(shell);
	malloc_error();
}

t_env	*env_values(char *env)
{
	t_env	*new;
	char	**tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	tmp = ft_split_env(env, '=');
	if (!tmp)
	{
		free(new);
		return (NULL);
	}
	new->key = tmp[0];
	new->value = ft_strdup(getenv(new->key));
	if (!new->value)
	{
		free_env_value(tmp, new);
		return (NULL);
	}
	new->next = NULL;
	if (tmp[1])
		free(tmp[1]);
	free (tmp);
	return (new);
}

t_env	*environ(t_shell *shell, char **envp)
{
	t_env	*new;
	t_env	*tmp;
	int		i;

	i = 1;
	if (!envp || envp[0] == NULL)
		return (NULL);
	new = env_values(envp[0]);
	if (!new)
		free_all_malloc(shell);
	tmp = new;
	while (envp[i])
	{
		new->next = env_values(envp[i]);
		if (!new->next)
			free_environ(shell, tmp, i);
		new = new->next;
		i++;
	}
	new = tmp;
	return (new);
}

char	*search_env(t_shell *shell, char *key)
{
	t_env	*tmp;

	tmp = shell->envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
