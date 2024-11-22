/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:56:01 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/22 19:18:07 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	heredoc_loop(t_shell *shell, t_group *group, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || (ft_strcmp(line, group->next->word) == 0)
			|| g_signal == SIGINT)
		{
			free(line);
			break ;
		}
		subs_hd(shell, line, fd);
		free(line);
	}
	close(fd);
	if (!line)
		hd_error(group->next->word);
}

void	create_heredoc(t_shell *shell, t_group *group, int hd_num)
{
	int		fd;
	char	*doc;
	char	*num;

	doc = "/tmp/heredoc";
	num = ft_itoa(hd_num);
	if (!num)
		free_all_malloc(shell);
	doc = ft_strjoin(doc, num);
	free(num);
	if (!doc)
		free_all_malloc(shell);
	group->file = doc;
	fd = open(doc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror_error(shell, doc);
		return ;
	}
	heredoc_loop(shell, group, fd);
}

void	read_heredocs(t_shell *shell)
{
	t_group	*tmp;
	int		hd_num;

	init_signal_hd();
	hd_num = 0;
	tmp = shell->groups;
	while (tmp && g_signal != SIGINT)
	{
		if (tmp->type == REDIR_HD)
		{
			create_heredoc(shell, tmp, hd_num);
			hd_num++;
		}
		tmp = tmp->next;
	}
}
