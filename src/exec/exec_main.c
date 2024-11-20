/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:12:00 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/20 21:44:19 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_everything(t_shell *shell)
{
	int		pipe_n;
	int		i;
	int 	j;
	int 	pipe_fd[2];
	int 	prev_fd;
	t_group *group;
	int		*pids;
	char	*cmd;
	int		fork_n;

	group = shell->groups;
	read_heredocs(shell);
	cmd = get_cmd(shell, group);
	if (!cmd)
	{
		if (group)
			handle_redirections(shell, group);
		return ;
	}
	if (g_signal != SIGINT)
	{
		init_signal_quit();
		prev_fd = -1;
		pipe_n = count_pipes(shell->groups);
		i = 0;
		fork_n = 0;
		j = is_builtin(cmd);
		free(cmd);
		if (pipe_n == 0 && j)
		{
			if (!save_restore_fds(0))
			{
				free_all(shell);
				exit(1);
			}
			exec_block(shell, group);
			if (!save_restore_fds(1))
			{
				free_all(shell);
				exit(1);
			}
		}
		else
		{
			pids = malloc(sizeof(int) * (pipe_n + 1));
			if (!pids)
				free_all_malloc(shell);
			while (i <= pipe_n)
			{
				if (i < pipe_n)
				{
					if (pipe(pipe_fd) == -1)
					{
						perror("pipe");
						shell->exit_status = 1;
						break ;
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
					break ;
				}
				if (pids[i] > 0)
					fork_n++;
				if (pids[i] == 0)
				{
					signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
					if (pipe_fd[0] >= 0)
						close(pipe_fd[0]);
					redirect_pipes(prev_fd, pipe_fd[1]);
					exec_block(shell, group);
					i = shell->exit_status;
					free(pids);
					free_all(shell);
					exit(i);
				}
				if (prev_fd != -1)
					close(prev_fd);
				if (pipe_fd[1] != -1)
					close(pipe_fd[1]);
				advance_group(&group);
				prev_fd = pipe_fd[0];
				i++;
			}
			i = 0;
			while (i < fork_n)
			{
				waitpid(pids[i], &shell->exit_status, 0);
				if (WIFEXITED(shell->exit_status))
					shell->exit_status = WEXITSTATUS(shell->exit_status);
				i++;
			}
			free(pids);
		}
		if (fork_n < pipe_n + 1 && !j)
		{
			free_all(shell);
			exit(1);
		}
	}
	init_signal();
}
