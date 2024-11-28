/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:27:05 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/28 21:22:36 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	args_cd_error(t_shell *shell)
{
	ft_putstr_fd("minishell: cd: too many arguments\n", 2);
	shell->exit_status = 1;
}

void	file_cd_error(t_shell *shell, char **args, char *file, char *oldpwd)
{
	char	*aux;
	char	*str;

	aux = ft_strjoin("minishell: cd: ", file);
	if (!aux)
	{
		free(oldpwd);
		free(args);
		free_all_malloc(shell);
	}
	str = ft_strjoin(aux, get_cd_error(file));
	free(aux);
	if (!str)
	{
		free(oldpwd);
		free(args);
		free_all_malloc(shell);
	}
	ft_putstr_fd(str, 2);
	free(str);
	shell->exit_status = 1;
}

void	update_pwd(t_shell *shell, char *oldpwd)
{
	t_env	*tmp;
	char	*aux;
	int		found_old;

	found_old = 0;
	tmp = shell->envp;
	while (tmp)
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
			found_old = 1;
		}
		tmp = tmp->next;
	}
	if (!found_old)
		free(oldpwd);
}

char	*cd_home(t_shell *shell)
{
	char	*oldpwd;
	char	*home;

	oldpwd = getcwd(NULL, 0);
	home = search_env(shell, "HOME");
	if (!home)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		shell->exit_status = 1;
		return (oldpwd);
	}
	if (chdir(home) == -1)
		file_cd_error(shell, NULL, home, oldpwd);
	return (oldpwd);
}

void	cd(t_shell *shell, char **args)
{
	char	*oldpwd;

	if (!args || !args[0])
		oldpwd = cd_home(shell);
	else if (args[0] && args[1])
	{
		args_cd_error(shell);
		oldpwd = NULL;
	}
	else if (!args[0][0])
		oldpwd = getcwd(NULL, 0);
	else
	{
		oldpwd = getcwd(NULL, 0);
		if (chdir(args[0]) == -1)
			file_cd_error(shell, args, args[0], oldpwd);
	}
	if (shell->exit_status || !shell->envp)
	{
		free(oldpwd);
		return ;
	}
	update_pwd(shell, oldpwd);
}
