/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:09:53 by albmarqu          #+#    #+#             */
/*   Updated: 2024/12/13 16:37:03 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_pwd(t_shell *shell)
{
	char	*pwd[2];
	char	*cwd;

	if (!search_env(shell, "PWD"))
	{
		cwd = getcwd(NULL, 0);
		pwd[0] = ft_strjoin("PWD=", cwd);
		if (!pwd[0])
		{
			free(cwd);
			free_all_malloc(shell);
		}
		pwd[1] = NULL;
		free(cwd);
		if (!export(shell, pwd))
		{
			free(pwd[0]);
			free_all_malloc(shell);
		}
		free(pwd[0]);
	}
}

void	set_oldpwd(t_shell *shell)
{
	char	*oldpwd[2];

	if (!search_env(shell, "OLDPWD"))
	{
		oldpwd[0] = "OLDPWD";
		oldpwd[1] = NULL;
		if (!export(shell, oldpwd))
			free_all_malloc(shell);
	}
}

void	set_path(t_shell *shell)
{
	char	*path[2];

	if (!search_env(shell, "PATH"))
	{
		path[0] = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
		path[1] = NULL;
		if (!export(shell, path))
			free_all_malloc(shell);
	}
}

void	set_(t_shell *shell)
{
	char	*underscore[2];

	if (!search_env(shell, "_"))
	{
		if (search_env(shell, "SHELL"))
		{
			underscore[0] = ft_strjoin("_=", search_env(shell, "SHELL"));
			underscore[1] = NULL;
			export(shell, underscore);
		}
		else
		{
			underscore[0] = "_=./minishell";
			underscore[1] = NULL;
			export(shell, underscore);
		}
	}
}

void	set_env_var(t_shell *shell)
{
	set_pwd(shell);
	set_oldpwd(shell);
	set_path(shell);
	set_shlvl(shell);
}
