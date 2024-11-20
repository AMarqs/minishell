/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:48:48 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/20 21:49:27 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_cmd(t_shell *shell, t_group *group)
{
	t_group	*tmp;
	char	*cmd;

	tmp = group;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD)
		{
			cmd = ft_strdup(tmp->word);
			if (!cmd)
				free_all_malloc(shell);
			return (cmd);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	**get_args(t_group *groups)
{
	t_group	*tmp;
	char	**args;
	int		i;

	if (!groups)
		return (NULL);
	i = 0;
	tmp = groups;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == ARG || tmp->type == CMD)
			i++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL);
	i = 0;
	tmp = groups;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == ARG || tmp->type == CMD)
			args[i++] = tmp->word;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

char	*get_path(t_shell *shell, char **env, char *cmd)
{
	int		i;
	char	*tmp;
	char	*aux;
	char	**path;

	path = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			shell->path = env[i] + 5;
			path = ft_split(env[i] + 5, ':');
			if (!path)
			{
				free(cmd);
				free_all_malloc(shell);
			}
		}
		i++;
	}
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
		{
			free_all(shell);
			free_array(path);
			free(cmd);
			malloc_error();
		}
		aux = ft_strjoin(tmp, cmd);
		if (!aux)
		{
			free_all(shell);
			free(tmp);
			free(cmd);
			free_array(path);
			malloc_error();
		}
		free(tmp);
		if (!access(aux, F_OK))
		{
			free_array(path);
			return (aux);
		}
		free(aux);
		i++;
	}
	free_array(path);
	return (NULL);
}
