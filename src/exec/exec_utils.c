/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:54:24 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/20 21:49:32 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

int	count_pipes(t_group *groups)
{
	t_group	*tmp;
	int		pipe_n;

	pipe_n = 0;
	tmp = groups;
	while (tmp)
	{
		if (tmp->type == PIPE)
			pipe_n++;
		tmp = tmp->next;
	}
	return (pipe_n);
}

int	check_path(char *path)
{
	int	i;

	i = 1;
	if (!path)
		return (0);
	if (path[0] == '\0')
		return (0);
	if (path[0] == ':')
		return (2);
	while (path[i])
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == '\0')
				return (2);
			if (path[i + 1] == ':')
				return (2);
		}
		i++;
	}
	return (1);
}

void	redirect_pipes(int prev_fd, int next_fd)
{
	if (prev_fd >= 0)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			close(prev_fd);
			perror("Fatal error: dup2");
			exit(1);
		}
		close(prev_fd);
	}
	if (next_fd >= 0)
	{
		if (dup2(next_fd, STDOUT_FILENO) == -1)
		{
			close(next_fd);
			perror("Fatal error: dup2");
			exit(1);
		}
		close(next_fd);
	}
}

void	advance_group(t_group **group)
{
	t_group	*tmp;

	tmp = *group;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	if (tmp && tmp->type == PIPE)
		*group = tmp->next;
}
