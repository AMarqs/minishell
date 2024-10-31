/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 13:07:32 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/31 13:07:51 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pwd(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		printf("minishell: pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		shell->exit_status = 1;
		return ;
	}
	printf("%s\n", pwd);
	free(pwd);
	shell->exit_status = 0;
}