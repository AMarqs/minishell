/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:49:46 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/21 19:50:19 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_child(t_shell *shell, int *pipe_fd, int *pids, int i)
{
	int		pipe_n;

	pipe_n = count_pipes(shell->groups);
	if (i < pipe_n)
	{
		if (pipe(pipe_fd) == -1)
		{
			perror("pipe");
			shell->exit_status = 1;
			return (0);
		}
	}
	else
	{
		pipe_fd[0] = -1;
		pipe_fd[1] = -1;
	}
	pids[i] = fork();
	if (pids[i] == -1)
	{
		perror("fork");
		shell->exit_status = 1;
		return (0);
	}
	return (1);
}

void	exec_child(t_shell *shell, t_group *group, t_fd fd, int *pids)
{
	int	i;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (fd.pipe_fd[0] >= 0)
		close(fd.pipe_fd[0]);
	redirect_pipes(fd.prev_fd, fd.pipe_fd[1]);
	exec_block(shell, group);
	i = shell->exit_status;
	free(pids);
	free_all(shell);
	exit(i);
}

int	exec_pipes_loop(t_shell *shell, t_group *group, int fork_n, int *pids)
{
	int		i;
	t_fd	fd;
	int		pipe_n;

	i = 0;
	fd.prev_fd = -1;
	pipe_n = count_pipes(shell->groups);
	while (i <= pipe_n)
	{
		if (!init_child(shell, fd.pipe_fd, pids, i))
			break ;
		if (pids[i] > 0)
			fork_n++;
		if (pids[i] == 0)
			exec_child(shell, group, fd, pids);
		if (fd.prev_fd != -1)
			close(fd.prev_fd);
		if (fd.pipe_fd[1] != -1)
			close(fd.pipe_fd[1]);
		advance_group(&group);
		fd.prev_fd = fd.pipe_fd[0];
		i++;
	}
	return (fork_n);
}

int	exec_pipes(t_shell *shell, t_group *group, int fork_n)
{
	int		*pids;
	int		pipe_n;
	int		i;

	i = 0;
	pipe_n = count_pipes(shell->groups);
	pids = malloc(sizeof(int) * (pipe_n + 1));
	if (!pids)
		free_all_malloc(shell);
	fork_n = exec_pipes_loop(shell, group, fork_n, pids);
	while (i < fork_n)
	{
		waitpid(pids[i], &shell->exit_status, 0);
		if (WIFEXITED(shell->exit_status))
			shell->exit_status = WEXITSTATUS(shell->exit_status);
		i++;
	}
	free(pids);
	return (fork_n);
}
