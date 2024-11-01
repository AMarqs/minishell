/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:09:44 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/01 13:17:58 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_shell(t_shell *shell, int x)
{
	// t_env	*tmp;
	// t_env	*aux;

	if (x)
	{
		free_all(shell);
	}
	exit(shell->exit_status);
}
