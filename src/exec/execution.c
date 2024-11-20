/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:44:54 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/20 21:45:17 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_cmd(t_shell *shell, t_group *group)
{
	char	*cmd;
	int		i;
	char	**env;

	cmd = get_cmd(shell, group);
	if (!cmd)
		return ;
	i = is_builtin(cmd);
	if (i)
	{
		free(cmd);
		exec_builtin(shell, group, i);
		return ;
	}
	env = get_envp(shell);
	if (!env)
	{
		free(cmd);
		save_restore_fds(1);
		free_all_malloc(shell);
	}
	check_cmd(shell, group, cmd, env);
}

void	exec_block(t_shell *shell, t_group *group)
{
	handle_redirections(shell, group);
	if (shell->exit_status)
		return ;
	exec_cmd(shell, group);
}
