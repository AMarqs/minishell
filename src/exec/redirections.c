/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:01:08 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/08 13:54:20 by glopez-c         ###   ########.fr       */
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
		// shell->exit_status = 0;
		dup2(fd, STDIN_FILENO);
	}
	close(fd);
}

void	output_redirection(t_shell *shell, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
		perror("");
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
		ft_putstr_fd(": ", 2);
		perror("");
		shell->exit_status = 1;
	}
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	heredoc_redirection(t_shell *shell, int i)
{
	char	*doc;
	int		fd;
	
	doc = "/tmp/heredoc";
	doc = ft_strjoin(doc, ft_itoa(i));
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
		dup2(fd, STDIN_FILENO);
	free(doc);
	close(fd);
}

void	handle_redirections(t_shell *shell, t_group *group)
{
	t_group	*tmp;
	int		hd_num;

	tmp = group;
	hd_num = count_hd(shell->groups);
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == REDIR_IN)
			input_redirection(shell, tmp->next->word);
		if (tmp->type == REDIR_OUT)
			output_redirection(shell, tmp->next->word);
		if (tmp->type == REDIR_APPEND)
			append_redirection(shell, tmp->next->word);
		if (tmp->type == REDIR_HD)
			heredoc_redirection(shell, hd_num - count_hd(tmp));
		if (shell->exit_status != 0)
			break ;
		tmp = tmp->next;
	}
}
