/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:44:53 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/20 18:40:51 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	malloc_error(void)
{
	ft_putstr_fd("Fatal error: malloc: memory allocation error\n", 2);
	exit(1);
}

void	free_all_malloc(t_shell *shell)
{
	free_all(shell);
	malloc_error();
}

void	hd_error(char *word)
{
	ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
	ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
	ft_putstr_fd(word, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

void	perror_error(t_shell *shell, char *word)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(word, 2);
	ft_putstr_fd(": ", 2);
	perror("");
	shell->exit_status = 1;
}
