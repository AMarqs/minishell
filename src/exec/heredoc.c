/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:56:01 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/19 15:28:45 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	count_hd(t_group *groups)
{
	t_group	*tmp;
	int		hd;

	hd = 0;
	tmp = groups;
	while (tmp)
	{
		if (tmp->type == REDIR_HD)
			hd++;
		tmp = tmp->next;
	}
	return (hd);
}

void	subs_hd(t_shell *shell, char *line, int fd)
{
	char	*tmp;
	int		i;
	int		j;
	int		len;
	char	*var;
	char	*exit_status;

	i = 0;
	var = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			if (!line[i + 1] || !(line[i + 1] == '_'
					|| ft_isalpha(line[i + 1]) || line[i + 1] == '?'))
			{
				ft_putchar_fd('$', fd);
				if (line[i + 1] == '\0')
					break ;
			}
			else
			{
				if (line[++i] == '?')
				{
					exit_status = ft_itoa(shell->prev_status);
					if (!exit_status)
					{
						close(fd);
						free_all_malloc(shell);
					}
					ft_putstr_fd(exit_status, fd);
				}
				else
				{
					j = i;
					len = 0;
					if (line[i] && (ft_isalpha(line[i]) || line[i + 1] == '_'))
					{
						while (line[i] && (ft_isalnum(line[i])
								|| line[i] == '_'))
						{
							len++;
							i++;
						}
						var = malloc(sizeof(char) * (len + 1));
						if (!var)
						{
							close(fd);
							free_all_malloc(shell);
						}
						i = j;
						j = 0;
						while (j < len)
						{
							var[j] = line[i];
							i++;
							j++;
						}
						i--;
						var[j] = '\0';
						tmp = search_env(shell, var);
						free(var);
						if (tmp)
							ft_putstr_fd(tmp, fd);
					}
				}
			}
		}
		else
			ft_putchar_fd(line[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}

void	create_heredoc(t_shell *shell, t_group *group, int hd_num)
{
	int		fd;
	char	*line;
	char	*doc;
	char	*num;

	doc = "/tmp/heredoc";
	num = ft_itoa(hd_num);
	if (!num)
		free_all_malloc(shell);
	doc = ft_strjoin(doc, num);
	if (!doc)
		free_all_malloc(shell);
	group->file = doc;
	fd = open(doc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(doc, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		shell->exit_status = 1;
		return ;
	}
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
	{
		ft_putstr_fd("minishell: warning: here-document ", STDERR_FILENO);
		ft_putstr_fd("delimited by end-of-file (wanted `", STDERR_FILENO);
		ft_putstr_fd(group->next->word, STDERR_FILENO);
		ft_putendl_fd("')", STDERR_FILENO);
	}
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
