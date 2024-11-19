/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:09:44 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/19 12:21:04 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	num_exit_error(t_shell *shell, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	shell->exit_status = 2;
}

void	args_exit_error(t_shell *shell)
{
	ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	shell->exit_status = 1;
}

void	exit_args(t_shell *shell, char **args)
{
	int	i;
	int	arg;

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
		while (args[0][i++])
		{
			if (ft_isdigit(args[0][i - 1]) == 0 && args[0][i - 1] != ' '
				&& args[0][i - 1] != '\t')
			{
				num_exit_error(shell, args[0]);
				break ;
			}
		}
	}
	if (arg > 1 && shell->exit_status == 0)
		args_exit_error(shell);
}

void	exit_shell(t_shell *shell, char **args)
{
	int	i;

	//ft_putstr_fd("exit\n", 1);
	if (args)
	{
		exit_args(shell, args);
		if (args[0] && shell->exit_status == 0)
			shell->exit_status = (unsigned char)ft_atoi(args[0]);
	}
	free(args);
	i = shell->exit_status;
	save_restore_fds(1);
	free_all(shell);
	exit(i);
}
