/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:12:00 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/06 19:36:22 by glopez-c         ###   ########.fr       */
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
		if (tmp->type == ARG || tmp->type == CMD)
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
		if (tmp->type == ARG || tmp->type == CMD)
			args[i++] = tmp->word;
		tmp = tmp->next;
	}
	args[i] = NULL;
	print_array(args);
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

void	input_redirection(t_shell *shell, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->exit_status = 1;
	}
	else
		dup2(fd, STDIN_FILENO);
	close(fd);
}

void	output_redirection(t_shell *shell, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->exit_status = 1;
	}
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	append_redirection(t_shell *shell, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		shell->exit_status = 1;
	}
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	heredoc_redirection(t_shell *shell, char *word)
{
	int		fd;
	char	*line;

	fd = open("/tmp/heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: heredoc: No such file or directory\n", 2);
		shell->exit_status = 1;
	}
	else
	{
		while (1)
		{
			line = readline("> ");
			if (!line || (ft_strcmp(line, word) == 0))
			{
				free(line);
				break ;
			}
			ft_putstr_fd(line, fd);
			ft_putstr_fd("\n", fd);
			free(line);
		}
		close(fd);
		fd = open("/tmp/heredoc", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

void	handle_redirections(t_shell *shell, t_group *group)
{
	t_group	*tmp;

	tmp = group;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN)
		{
			input_redirection(shell, tmp->next->word);
		}
		if (tmp->type == REDIR_OUT)
		{
			output_redirection(shell, tmp->next->word);
		}
		if (tmp->type == REDIR_APPEND)
		{
			append_redirection(shell, tmp->next->word);
		}
		if (tmp->type == REDIR_HD)
		{
			heredoc_redirection(shell, tmp->next->word);
		}
		tmp = tmp->next;
	}
}

char	*find_cmd(t_group *group)
{
	t_group	*tmp;

	tmp = group;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == CMD)
			return (tmp->word);
		tmp = tmp->next;
	}
	return (NULL);
}

char	**get_envp(t_env *envp)
{
	t_env	*tmp;
	char	**env;
	int		i;
	char	*tmp2;

	tmp = envp;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (NULL); /////////////////////// ADD ERROR FUNCTION
	i = 0;
	tmp = envp;
	while (tmp)
	{
		if (tmp->value)
		{
			tmp2 = ft_strjoin(tmp->key, "=");
			env[i] = ft_strjoin(tmp2, tmp->value);
		}
		else
			env[i] = ft_strdup(tmp->key);
		i++;
		tmp = tmp->next;
	}
	env[i] = NULL;
	return (env);
}

void	exec_cmd(t_shell *shell, t_group *group)
{
	int		i;
	//int		child;
	char	**args;
	char	*cmd;
	char	**env;

	cmd = find_cmd(group);
	if (!cmd)
		return ;
	i = is_builtin(group->word);
	if (i)
	{
		exec_builtin(shell, group, i, 0);
		return ;
	}
	args = get_args(group);
	// printf("cmd: %s\n", cmd);
	// print_groups(group);
	env = get_envp(shell->envp);
	execve(group->word, args, env);
	// child = fork();
	// if (child == 0)
	// {
	// 	execve(group->word, args, env);
	// 	write(2, "minishell: ", 11);
	// 	ft_putstr_fd(group->word, 2);
	// 	ft_putstr_fd(": command not found\n", 2);
	// 	shell->exit_status = 127;
	// 	free(args);
	// 	exit(127);
	// }
	// else if (child < 0)
	// {
	// 	perror("fork");
	// 	shell->exit_status = 1;
	// }
	// else
	// {
	// 	waitpid(child, &shell->exit_status, 0);
	// 	if (WIFEXITED(shell->exit_status))
	// 		shell->exit_status = WEXITSTATUS(shell->exit_status);
	// 	printf("exit_status: %d\n", shell->exit_status);
	// }
	free(args);
}

void	exec_block(t_shell *shell, t_group *group)
{
	handle_redirections(shell, group);
	exec_cmd(shell, group);
}

void	exec_everything(t_shell *shell)
{
	// t_group	*tmp;
	int		pipe_n;
	// int		i;
	int pid;
	int pipe_fd[2];
	int prev_fd[2];

	save_restore_fds(0);
	// i = is_builtin(shell->groups->word);
	pipe_n = count_pipes(shell->groups);
	
	while (pipe_n >= 0)
	{
		if (pipe_n > 0)
		{
			pipe(pipe_fd);
		}
		pid = fork();
		if (pid == 0)
		{
			exec_block(shell, shell->groups);
			exit(0);
		}
		else if (pid < 0)
		{
			perror("fork");
			shell->exit_status = 1;
		}
		prev_fd[0] = pipe_fd[0];
		pipe_n--;
	}



	// if (pipe_n == 0 && i)
	// {
	// 	tmp = shell->groups;
	// 	if (tmp->type == CMD)
	// 		exec_builtin(shell, shell->groups, i, 0);
	// }
	// else if (pipe_n == 0)

	
	// if (pipe_n == 0)
	// {
	// 	exec_block(shell, shell->groups);
	// }
	// else
	// 	exec_pipes(shell);
	// {
	// 	tmp = shell->groups;
	// 	if (tmp->type == CMD)
	// 		exec_cmd(shell, tmp->word);
	// }
	save_restore_fds(1);
}
