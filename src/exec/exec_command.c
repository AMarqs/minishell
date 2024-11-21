/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:17:37 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/21 17:56:21 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_script(t_shell *shell, char *cmd, char **env)
{
	if (access(cmd, F_OK))
	{
		no_file_error(shell, cmd);
		free_envp(env, cmd);
		return (0);
	}
	else if (is_directory(cmd))
	{
		is_directory_error(shell, cmd);
		free_envp(env, cmd);
		return (0);
	}
	if (access(cmd, X_OK | R_OK))
	{
		permission_denied_error(shell, cmd);
		free_envp(env, cmd);
		return (0);
	}
	return (1);
}

int	check_command_file(t_shell *shell, char *cmd, char **env)
{
	if (access(cmd, F_OK))
	{
		no_file_error(shell, cmd);
		free_envp(env, cmd);
		return (0);
	}
	else if (is_directory(cmd))
	{
		is_directory_error(shell, cmd);
		free_envp(env, cmd);
		return (0);
	}
	return (1);
}

char	*check_command(t_shell *shell, char *cmd, char **env)
{
	char	*found;
	int		x;

	found = get_path(shell, env, cmd);
	x = check_path(shell->path);
	if (x == 0 && !found)
	{
		if (!check_command_file(shell, cmd, env))
			return (NULL);
	}
	else if (!found)
	{
		if ((x == 2 && access(cmd, F_OK)) || x != 2)
		{
			command_not_found_error(shell, cmd);
			free_envp(env, cmd);
			return (NULL);
		}
	}
	else
	{
		free(cmd);
		cmd = found;
	}
	return (cmd);
}

char	*checking_cmd(t_shell *shell, char *cmd, char **env)
{
	if (ft_strnstr(cmd, "/", ft_strlen(cmd)))
	{
		if (!check_script(shell, cmd, env))
			return (NULL);
	}
	else
	{
		cmd = check_command(shell, cmd, env);
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}

void	check_cmd(t_shell *shell, t_group *group, char *cmd, char **env)
{
	char	**args;

	cmd = checking_cmd(shell, cmd, env);
	if (!cmd)
		return ;
	if (access(cmd, X_OK))
		permission_denied_error(shell, cmd);
	else if (access(cmd, R_OK))
		cannot_open_error(shell, cmd);
	if ((access(cmd, X_OK)) || (access(cmd, R_OK)))
	{
		free_envp(env, cmd);
		return ;
	}
	args = get_args(group);
	if (!args)
	{
		free_envp(env, cmd);
		save_restore_fds(1);
		free_all_malloc(shell);
	}
	execve(cmd, args, env);
}
