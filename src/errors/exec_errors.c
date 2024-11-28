/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:08:34 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/28 20:26:15 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	no_file_error(t_shell *shell, char *cmd)
{
	char	*aux;
	char	*str;

	aux = ft_strjoin("minishell: ", cmd);
	free(cmd);
	if (!aux)
		free_all_malloc(shell);
	str = ft_strjoin(aux, ": No such file or directory\n");
	free(aux);
	if (!str)
		free_all_malloc(shell);
	ft_putstr_fd(str, 2);
	free(str);
	shell->exit_status = 127;
}

void	is_directory_error(t_shell *shell, char *cmd)
{
	char	*aux;
	char	*str;

	aux = ft_strjoin("minishell: ", cmd);
	free(cmd);
	if (!aux)
		free_all_malloc(shell);
	str = ft_strjoin(aux, ": Is a directory\n");
	free(aux);
	if (!str)
		free_all_malloc(shell);
	ft_putstr_fd(str, 2);
	free(str);
	shell->exit_status = 126;
}

void	permission_denied_error(t_shell *shell, char *cmd)
{
	char	*aux;
	char	*str;

	aux = ft_strjoin("minishell: ", cmd);
	if (!aux)
		free_all_malloc(shell);
	str = ft_strjoin(aux, ": Permission denied\n");
	free(aux);
	if (!str)
		free_all_malloc(shell);
	ft_putstr_fd(str, 2);
	free(str);
	shell->exit_status = 126;
}

void	command_not_found_error(t_shell *shell, char *cmd)
{
	char	*aux;
	char	*str;

	aux = ft_strjoin("minishell: ", cmd);
	free(cmd);
	if (!aux)
		free_all_malloc(shell);
	str = ft_strjoin(aux, ": command not found\n");
	free(aux);
	if (!str)
		free_all_malloc(shell);
	ft_putstr_fd(str, 2);
	free(str);
	shell->exit_status = 127;
}

void	cannot_open_error(t_shell *shell, char *cmd)
{
	char	*aux;
	char	*str;

	aux = ft_strjoin("/bin/sh: 0: cannot open ", cmd);
	if (!aux)
		free_all_malloc(shell);
	str = ft_strjoin(aux, ": Permission denied\n");
	free(aux);
	if (!str)
		free_all_malloc(shell);
	ft_putstr_fd(str, 2);
	free(str);
	shell->exit_status = 2;
}
