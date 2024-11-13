/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 21:12:00 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/13 14:10:30 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

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
	return (args);
}

void	exec_builtin(t_shell *shell, t_group *group, int i, int child)
{
	char	**args;

	while (group && group->type != CMD)
		group = group->next;
	args = get_args(group->next);
	if (i == 1)
		cd(shell, args);
	if (i == 2)
		ft_echo(shell, args);
	if (i == 3)
		env(shell);
	if (i == 4)
		exit_shell(shell, child, args);
	if (i == 5)
		export(shell, args);
	if (i == 6)
		pwd(shell);
	if (i == 7)
		unset(shell, args);
	free(args);
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

char	*get_path(t_shell *shell, char **env, char *cmd)
{
	int		i;
	char	*tmp;
	char	**path;

	path = NULL;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			shell->path = env[i] + 5;
			path = ft_split(env[i] + 5, ':');
		}
		i++;
	}
	if (!path)
	{
		return (NULL);
	}
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		path[i] = ft_strjoin(tmp, cmd);
		if (!access(path[i], F_OK))
		{
			free(tmp);
			return (path[i]);
		}
		i++;
	}
	return (NULL);
}

int	check_path(char *path)
{	
	int	i;

	i = 1;
	if (!path)
		return (0);
	if (path[0] == '\0')
		return (0);
	if (path[0] == ':')
		return (2);
	while (path[i])
	{
		if (path[i] == ':')
		{
			if (path[i + 1] == '\0')
				return (2);
			if (path[i + 1] == ':')
				return (2);
		}
		i++;
	}
	return (1);
}

void	exec_cmd(t_shell *shell, t_group *group)
{
	int		i;
	char	**args;
	char	*cmd;
	char	**env;
	char	*found;
	
	cmd = find_cmd(group);
	if (!cmd)
		return ;
	i = is_builtin(cmd);
	if (i)
	{
		exec_builtin(shell, group, i, 0);
		return ;
	}
	args = get_args(group);
	env = get_envp(shell->envp);
	if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/'
		|| cmd[ft_strlen(cmd) - 1] == '/' || ft_strnstr(cmd, "/", ft_strlen(cmd)))
	{
		if (access(cmd, F_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("No such file or directory\n", 2);
			shell->exit_status = 127;
			return ;
		}
		else if (is_directory(cmd))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("Is a directory\n", 2);
			shell->exit_status = 126;
			return ;
		}
		if (access(cmd, X_OK | R_OK))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": ", 2);
			perror("");
			shell->exit_status = 126;
			return ;
		}
	}
	else
	{
		found = get_path(shell, env, cmd);
		int x = check_path(shell->path);
		if (x == 0 && !found)
		{
			if (access(cmd, F_OK))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd("No such file or directory\n", 2);
				shell->exit_status = 127;
				return ;
			}
			else if (is_directory(cmd))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd("Is a directory\n", 2);
				shell->exit_status = 126;
				return ;
			}
		}
		else if (!found && x == 2)
		{
			if (access(cmd, F_OK))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(cmd, 2);
				ft_putstr_fd(": ", 2);
				ft_putstr_fd("command not found\n", 2);
				shell->exit_status = 127;
				return ;
			}
		}
		else if (!found || (!found && access(cmd, F_OK)))
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd("command not found\n", 2);
			shell->exit_status = 127;
			return ;
		}
		else
			cmd = found;
	}
	if (access(cmd, X_OK))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		perror("");  // Permission denied
		shell->exit_status = 126;
		return ;
	}
	if (access(cmd, R_OK))
	{
		ft_putstr_fd("/bin/sh: 0: cannot open ", 2);  // CAMBIAR POR MINISHELL: 0 ???
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		perror("");  // Permission denied
		shell->exit_status = 2;
		return ;
	}
	execve(cmd, args, env);
	free(args);
}

void	exec_block(t_shell *shell, t_group *group)
{
	handle_redirections(shell, group);
	if (shell->exit_status)
		return ;
	exec_cmd(shell, group);
}

void	redirect_pipes(int prev_fd, int next_fd)
{
	// printf("prev_fd: %d, next_fd: %d\n", prev_fd, next_fd);
	if (prev_fd >= 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (next_fd >= 0)
	{
		dup2(next_fd, STDOUT_FILENO);
		close(next_fd);
	}
}

void	advance_group(t_group **group)
{
	t_group	*tmp;

	tmp = *group;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	if (tmp && tmp->type == PIPE)
		*group = tmp->next;
}

void	exec_everything(t_shell *shell)
{
	int		pipe_n;
	int		i;
	int 	pipe_fd[2];
	int 	prev_fd;
	t_group *group;
	int		*pids;
	char	*cmd;

	group = shell->groups;
	save_restore_fds(0);
	cmd = find_cmd(group);
	if (!cmd)
	{
		if (group)
			handle_redirections(shell, group);
		save_restore_fds(1);
		return ;
	}
	read_heredocs(shell);
	prev_fd = -1;
	pipe_n = count_pipes(shell->groups);
	pids = malloc(sizeof(int) * (pipe_n + 1));
	i = 0;
	if (pipe_n == 0 && is_builtin(cmd))
	{
		exec_block(shell, group);
	}
	else
	{
		while (i <= pipe_n)
		{
			if (i < pipe_n)
			{
				pipe(pipe_fd);
			}
			else
			{
				pipe_fd[0] = -1;
				pipe_fd[1] = -1;
			}
			pids[i] = fork();
			if (pids[i] == 0)
			{
				if (pipe_fd[0] >= 0)
					close(pipe_fd[0]);
				redirect_pipes(prev_fd, pipe_fd[1]);
				exec_block(shell, group);
				exit(shell->exit_status);
			}
			else if (pids[i] < 0)
			{
				perror("fork");
				shell->exit_status = 1;
			}
			if (prev_fd != -1) 
				close(prev_fd); // Close previous read end in parent
			if (pipe_fd[1] != -1) 
				close(pipe_fd[1]); // Close write end in parent
			advance_group(&group);
			prev_fd = pipe_fd[0];
			i++;
		}
		i = 0;
		while (i <= pipe_n)
		{
			waitpid(pids[i], &shell->exit_status, 0);
			if (WIFEXITED(shell->exit_status))
				shell->exit_status = WEXITSTATUS(shell->exit_status);
			i++;
		}
	}
	free(pids);
	save_restore_fds(1);
}
