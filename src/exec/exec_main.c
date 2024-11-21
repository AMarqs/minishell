/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:12:00 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/21 19:50:26 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_one_builtin(t_shell *shell, t_group *group)
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

void	start_exec(t_shell *shell, t_group *group, char *cmd)
{
	int		j;
	int		pipe_n;
	int		fork_n;

	init_signal_quit();
	fork_n = 0;
	j = is_builtin(cmd);
	pipe_n = count_pipes(shell->groups);
	free(cmd);
	if (pipe_n == 0 && j)
		exec_one_builtin(shell, group);
	else
		fork_n = exec_pipes(shell, group, fork_n);
	if (fork_n < pipe_n + 1 && !j)
	{
		free_all(shell);
		exit(1);
	}
}

void	exec_everything(t_shell *shell)
{
	t_group	*group;
	char	*cmd;

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
		start_exec(shell, group, cmd);
	init_signal();
}
