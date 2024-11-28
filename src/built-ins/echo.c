/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 20:02:29 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/28 21:46:50 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_builtin(t_shell *shell, char **args)
{
	free(args);
	free_all_malloc(shell);
}

char	*add_n_flag(t_shell *shell, char **args, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(str, "\n");
	free(str);
	if (!tmp)
		free_builtin(shell, args);
	return (tmp);
}

char	*get_echo_string(t_shell *shell, char **args, int n_flag, int i)
{
	char	*str;
	char	*tmp;

	str = NULL;
	while (args[i++])
	{
		tmp = better_strjoin(str, args[i - 1]);
		free(str);
		if (!tmp)
			free_builtin(shell, args);
		str = tmp;
		if (args[i])
		{
			tmp = ft_strjoin(str, " ");
			free(str);
			if (!tmp)
				free_builtin(shell, args);
			str = tmp;
		}
	}
	if (!n_flag)
		str = add_n_flag(shell, args, str);
	return (str);
}

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
	int		i;
	int		n_flag;
	char	*str;

	i = 0;
	n_flag = 0;
	if (!args || !args[0])
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
	str = get_echo_string(shell, args, n_flag, i);
	ft_putstr_fd(str, 1);
	free(str);
	shell->exit_status = 0;
}
