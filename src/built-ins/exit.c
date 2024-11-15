/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:09:44 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/15 14:28:10 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	exit_args(char **args)
{
	int	i;
	int arg;

	arg = 0;
	while (args[arg])
		arg++;
	if (arg >= 1)
	{
		i = 0;
		if (args[0][0] == '-' || args[0][0] == '+')
			i++;
		while (ft_isspace(args[0][i]))
			i++;
		while (args[0][i])
		{
			if (ft_isdigit(args[0][i]) == 0 && args[0][i] != ' ' && args[0][i] != '\t')
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(args[0], 2);
				ft_putstr_fd(": numeric argument required\n", 2);
				return (2);
			}
			i++;
		}
	}
	if (arg > 1)
	{
		ft_putstr_fd("minishell: exit:", 2);
		ft_putstr_fd(" too many arguments\n", 2);
		return (1);
	}
	return (0);
}

void	exit_shell(t_shell *shell, int child, char **args)
{
	int	i;

	ft_putstr_fd("exit\n", 1);
	if (args)
	{
		i = exit_args(args);
		if (i)
			shell->exit_status = i;
		else if (args[0])
			shell->exit_status = (unsigned char)ft_atoi(args[0]);
	}
	free(args);
	if (!child)
		free_all(shell);
	exit(shell->exit_status);
}
