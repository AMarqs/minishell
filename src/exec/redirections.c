/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:01:08 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/29 17:50:04 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	input_redirection(t_shell *shell, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		perror_error(shell, file);
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("minishell: Fatal error: dup2");
			shell->exit_status = 1;
		}
	}
	close(fd);
}

void	output_redirection(t_shell *shell, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0700);
	if (fd < 0)
		perror_error(shell, file);
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: Fatal error: dup2");
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
		perror_error(shell, file);
	else
	{
		if (dup2(fd, STDOUT_FILENO) == -1)
		{
			perror("minishell: Fatal error: dup2");
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
		perror_error(shell, doc);
	else
	{
		if (dup2(fd, STDIN_FILENO) == -1)
		{
			perror("minishell: Fatal error: dup2");
			shell->exit_status = 1;
		}
	}
	close(fd);
}

void	handle_redirections(t_shell *shell, t_group *group, int flag_in)
{
	t_group	*tmp;

	tmp = group;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN && flag_in)
			input_redirection(shell, tmp->next->word);
		if (tmp->type == REDIR_OUT)
			output_redirection(shell, tmp->next->word);
		if (tmp->type == REDIR_APPEND)
			append_redirection(shell, tmp->next->word);
		if (tmp->type == REDIR_HD && flag_in)
			heredoc_redirection(shell, tmp->file);
		if (shell->exit_status != 0)
			break ;
		tmp = tmp->next;
	}
}
