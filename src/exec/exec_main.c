/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:12:00 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/05 13:29:14 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_pipes(t_group *groups)
{
	t_group	*tmp;
	int		pipe_n;

	pipe_n = 0;
	tmp = groups;
	while (tmp)
	{
		if (tmp->type == PIPE)
			pipe_n++;
		tmp = tmp->next;
	}
	return (pipe_n);
}

int	is_builtin(char *cmd)
{
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

char	**get_args(t_group *groups)
{
	t_group	*tmp;
	char	**args;
	int		i;

	if (!groups)
		return (NULL);
	i = 0;
	tmp = groups;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == ARG)
			i++;
		tmp = tmp->next;
	}
	args = malloc(sizeof(char *) * (i + 1));
	if (!args)
		return (NULL); /////////////////////// ADD ERROR FUNCTION
	i = 0;
	tmp = groups;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == ARG)
			args[i++] = tmp->word;
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}

void	exec_builtin(t_shell *shell, t_group *group, int i, int child)
{
	char	**args;

	args = get_args(group->next);
	if (i == 1)
		cd(shell, args);
	if (i == 2)
		ft_echo(shell, args);
	if (i == 3)
		env(shell);
	if (i == 4)
		exit_shell(shell, child);
	if (i == 5)
		export(shell, args);
	if (i == 6)
		pwd(shell);
	if (i == 7)
		unset(shell, args);
	free(args);
}

void	exec_everything(t_shell *shell)
{
	t_group	*tmp;
	int		pipe_n;
	int		i;

	i = is_builtin(shell->groups->word);
	pipe_n = count_pipes(shell->groups);
	if (pipe_n == 0 && i)
	{
		tmp = shell->groups;
		if (tmp->type == CMD)
			exec_builtin(shell, shell->groups, i, 0);
	}
	// else
	// 	exec_pipes(shell);
	// {
	// 	tmp = shell->groups;
	// 	if (tmp->type == CMD)
	// 		exec_cmd(shell, tmp->word);
	// }
}