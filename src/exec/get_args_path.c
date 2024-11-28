/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:48:48 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/28 21:28:10 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**fill_args(t_group *groups, char **args)
{
	t_group	*tmp;
	int		i;

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

char	**get_args(t_group *groups)
{
	t_group	*tmp;
	char	**args;
	int		i;

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
	args = fill_args(groups, args);
	return (args);
}

void	free_path(t_shell *shell, char **path, char *cmd)
{
	free(cmd);
	free_array(path);
	free_all_malloc(shell);
}

char	*search_command_path(t_shell *shell, char **path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*aux;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		if (!tmp)
			free_path(shell, path, cmd);
		aux = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!aux)
			free_path(shell, path, cmd);
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

char	*get_path(t_shell *shell, char **env, char *cmd)
{
	int		i;
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
	aux = search_command_path(shell, path, cmd);
	return (aux);
}
