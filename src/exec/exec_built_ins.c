/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:02:20 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/20 19:03:22 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (2);
	if (ft_strcmp(cmd, "env") == 0)
		return (3);
	if (ft_strcmp(cmd, "exit") == 0)
		return (4);
	if (ft_strcmp(cmd, "export") == 0)
		return (5);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (6);
	if (ft_strcmp(cmd, "unset") == 0)
		return (7);
	return (0);
}

void	exec_builtin(t_shell *shell, t_group *group, int i)
{
	char	**args;

	while (group && group->type != CMD)
		group = group->next;
	args = get_args(group->next);
	if (i == 1)
		cd(shell, args);
	else if (i == 2)
		ft_echo(shell, args);
	else if (i == 3)
		env(shell);
	else if (i == 4)
		exit_shell(shell, args);
	else if (i == 5 && !export(shell, args))
	{
		free(args);
		free_all_malloc(shell);
	}
	else if (i == 6)
		pwd(shell);
	else if (i == 7)
		unset(shell, args);
	free(args);
}
