/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:44:53 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/19 13:38:09 by albmarqu         ###   ########.fr       */
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