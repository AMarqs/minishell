/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:08:31 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/13 14:00:09 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	signal_handler(int signal)
{
	(void)signal;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// rl_done: cierra el readline del heredoc
void	signal_hd(int signal)
{
	g_signal = signal;
	rl_done = 1;
}

void	signal_quit(int signal)
{
	(void)signal;
	ft_putendl_fd("Quit (core dumped)", STDOUT_FILENO);
}
