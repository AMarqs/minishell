/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:15:42 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/20 14:57:57 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	save_fds(int *stdin, int *stdout)
{
	*stdin = dup(STDIN_FILENO);
	if (*stdin == -1)
	{
		perror("Fatal error: dup");
		return (0);
	}
	*stdout = dup(STDOUT_FILENO);
	if (*stdout == -1)
	{
		close(*stdin);
		perror("Fatal error: dup");
		return (0);
	}
	return (1);
}

int	restore_fds(int stdin, int stdout)
{
	if (dup2(stdin, STDIN_FILENO) == -1
		|| dup2(stdout, STDOUT_FILENO) == -1)
	{
		perror("minishell: Fatal error: dup2");
		close(stdin);
		close(stdout);
		return (0);
	}
	close(stdin);
	close(stdout);
	return (1);
}

int	save_restore_fds(int i)
{
	static int	stdin;
	static int	stdout;

	if (i == 0)
	{
		if (!save_fds(&stdin, &stdout))
			return (0);
	}
	else
	{
		if (!restore_fds(stdin, stdout))
			return (0);
	}
	return (1);
}
