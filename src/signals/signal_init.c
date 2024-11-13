/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:08:28 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/13 18:58:38 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// SIGQUIT es la senal ctrl+barra_invertida 
// SIGINT es la senal ctrl+C
// SIG_IGN ignora a la senal anterior
// 1. La funcion ignora la barra invertida mientras estamos esperando comando
// 2. Cuando reciba ctrl+C llama a la funcion signal_handler
// signal_handler: linea nueva y vuelve a mostrar minishel$
void	init_signal(void)
{
	g_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
}

// 1. La funcion ignora la barra invertida mientras estamos esperando comando
// 2. Cuando reciba ctrl+C llama a la funcion signal_hd
// signal_hd: cierra el readline del heredoc
void	init_signal_hd(void)
{
	g_signal = 0;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_hd);
}

// 1. Cuando reciba ctrl+barra_invertida  llama a la funcion signal_quit
// 2. La funcion ignora ctrl+C
// signal_quit: cierra el proceso con Core dumped
void	init_signal_quit(void)
{
	g_signal = 0;
	signal(SIGQUIT, signal_quit);
	signal(SIGINT, SIG_IGN);
}
