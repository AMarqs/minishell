/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:07:32 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/29 17:13:33 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pwd(t_shell *shell, char **args)
{
	char	*pwd;
	char	*str;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		str = "minishell: pwd: error retrieving current directory: ";
		str = ft_strjoin(str, "No such file or directory\n");
		if (!str)
			free_builtin(shell, args);
		ft_putstr_fd(str, 2);
		free(str);
		shell->exit_status = 1;
		return ;
	}
	str = ft_strjoin(pwd, "\n");
	free(pwd);
	if (!str)
		free_builtin(shell, args);
	ft_putstr_fd(str, 1);
	free(str);
	shell->exit_status = 0;
}
