/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:02:29 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/08 18:26:16 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_n_flag(char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
		if (arg[i++] != 'n')
			return (0);
	return (1);
}

void	ft_echo(t_shell *shell, char **args)
{
	int	i;
	int	n_flag;

	i = 0;
	n_flag = 0;
	if (!args)
	{
		ft_putstr_fd("\n", 1);
		shell->exit_status = 0;
		return ;
	}
	while (args[i] && is_n_flag(args[i]))
	{
		i++;
		n_flag = 1;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
	shell->exit_status = 0;
}
