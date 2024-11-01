/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 17:27:05 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/01 13:06:15 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	cd(t_shell *shell, char **args)
{
	char	*oldpwd;
	t_env	*tmp;
	char 	*aux;

	if (args[1])
	{
		shell->exit_status = 1;
		printf("minishell: cd: too many arguments\n");
		fflush(stdout);
		return ; /////////////////////// ADD ERROR FUNCTION
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(args[0]) == -1)
	{
		printf("minishell: cd: %s: No such file or directory\n", args[0]);
		fflush(stdout);
		shell->exit_status = 1;
		free(oldpwd);
		return ; /////////////////////// ADD ERROR FUNCTION
	}
	shell->exit_status = 0;
	if (!shell->envp)
	{
		return ; /////////////////////// ADD ERROR FUNCTION
	}
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