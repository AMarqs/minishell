/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:09:44 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/08 18:26:25 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	if (i > 1)
	{
		ft_putstr_fd("minishell: exit:", 2);
		ft_putstr_fd(" too many arguments\n", 2);
		return (1);
	}
	if (i == 1)
	{
		i = -1;
		if (args[0][0] == '-' || args[0][0] == '+')
			i++;
		while (args[0][++i])
		{
			if (ft_isdigit(args[0][i]) == 0)
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(args[0], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				return (2);
			}
		}
	}
	return (0);
}

void	exit_shell(t_shell *shell, int child, char **args)
{
	int	i;

	ft_putstr_fd("exit\n", 1);
	i = exit_args(args);
	if (i)
	{
		shell->exit_status = i;
		return ;
	}
	else if (args[0])
		shell->exit_status = (unsigned char)ft_atoi(args[0]);
	if (child)
	{
		free_all(shell);
	}
	//write(1, "exit\n", 5);
	exit(shell->exit_status);
}
