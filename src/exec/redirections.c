/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:01:08 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/15 13:57:43 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	input_redirection(t_shell *shell, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		shell->exit_status = 1;
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("minishell: Fatal error: dup2");
			shell->exit_status = 1; //////////////// FREE_ALL???
		}
	}
	close(fd);
}

void	output_redirection(t_shell *shell, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0700);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		shell->exit_status = 1;
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: Fatal error: dup2"); //////////////// FREE_ALL???
			shell->exit_status = 1;
		}
	}
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
		ft_putstr_fd(": ", 2);
		perror("");
		shell->exit_status = 1;
	}
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: Fatal error: dup2"); //////////////// FREE_ALL???
			shell->exit_status = 1;
		}
	}
	close(fd);
}

void	heredoc_redirection(t_shell *shell, char *doc)
{
	int		fd;
	
	fd = open(doc, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(doc, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		shell->exit_status = 1;
	}
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("minishell: Fatal error: dup2"); //////////////// FREE_ALL???
			shell->exit_status = 1;
		}
	}
	close(fd);
}

void	handle_redirections(t_shell *shell, t_group *group)
{
	t_group	*tmp;

	tmp = group;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN)
			input_redirection(shell, tmp->next->word);
		if (tmp->type == REDIR_OUT)
			output_redirection(shell, tmp->next->word);
		if (tmp->type == REDIR_APPEND)
			append_redirection(shell, tmp->next->word);
		if (tmp->type == REDIR_HD)
			heredoc_redirection(shell, tmp->file);
		if (shell->exit_status != 0)
			break ;
		tmp = tmp->next;
	}
}
