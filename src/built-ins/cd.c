/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:27:05 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/21 19:54:10 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	args_cd_error(t_shell *shell)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	shell->exit_status = 1;
}

void	file_cd_error(t_shell *shell, char *file, char *oldpwd)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	shell->exit_status = 1;
	free(oldpwd);
}

void	update_pwd(t_shell *shell, char *oldpwd)
{
	t_env	*tmp;
	char	*aux;

	tmp = shell->envp;
	while (tmp->next)
	{
		if (ft_strcmp(tmp->key, "PWD") == 0)
		{
			aux = tmp->value;
			tmp->value = getcwd(NULL, 0);
			free(aux);
		}
		if (ft_strcmp(tmp->key, "OLDPWD") == 0)
		{
			aux = tmp->value;
			tmp->value = oldpwd;
			free(aux);
		}
		tmp = tmp->next;
	}
}

void	cd(t_shell *shell, char **args)
{
	char	*oldpwd;

	if (args[1])
	{
		args_cd_error(shell);
		return ;
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(args[0]) == -1)
	{
		file_cd_error(shell, args[0], oldpwd);
		return ;
	}
	shell->exit_status = 0;
	if (!shell->envp)
	{
		free(oldpwd);
		return ;
	}
	update_pwd(shell, oldpwd);
}
