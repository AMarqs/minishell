/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 14:15:42 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/06 14:34:14 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	save_restore_fds(int i)
{
	static int	stdin;
	static int	stdout;

	if (i == 0)
	{
		stdin = dup(STDIN_FILENO);
		stdout = dup(STDOUT_FILENO);
	}
	else
	{
		dup2(stdin, STDIN_FILENO);
		dup2(stdout, STDOUT_FILENO);
		close(stdin);
		close(stdout);
	}
}
