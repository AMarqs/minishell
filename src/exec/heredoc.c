/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:56:01 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/11 11:13:54 by glopez-c         ###   ########.fr       */
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
	int 	len;
	char	*var;
	
	i = 0;
	var = NULL;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			if (ft_isspace(line[i]) || line[i] == '\0')
			{
				ft_putchar_fd('$', fd);
				ft_putchar_fd(line[i], fd);
				i++;
			}
			else
			{
				if (line[i] == '?')
				{
					ft_putstr_fd(ft_itoa(shell->prev_status), fd); ///// LEAK DE MEMORIA
					i++;
				}
				j = i;
				len = 0;
				if (line[i] && (ft_isalpha(line[i]) || line[i + 1] == '_'))
				{
					while (line[i] && (ft_isalnum(line[i]) || line[i] == '_'))
					{
						len++;
						i++;
					}
					var = malloc(sizeof(char) * (len + 1));
					i = j;
					j = 0;
					while (j < len)
					{
						var[j] = line[i];
						i++;
						j++;
					}
					var[j] = '\0';
					tmp = getenv(var);
					if (tmp)
					{
						ft_putstr_fd(tmp, fd);
					}
				}
				free(var);
			}
		}
		else
		{
			ft_putchar_fd(line[i], fd);
		}
		i++;
	}
	ft_putchar_fd('\n', fd);
}

void	create_heredoc(t_shell *shell, char *word, int hd_num)
{
	int		fd;
	char	*line;
	char	*doc;
	
	doc = "/tmp/heredoc";
	doc = ft_strjoin(doc, ft_itoa(hd_num));
	fd = open(doc, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	free(doc);
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
		if (!line || (ft_strcmp(line, word) == 0))
		{
			free(line);
			break ;
		}
		subs_hd(shell, line, fd);
		free(line);
	}
	close(fd);
}

void	read_heredocs(t_shell *shell)
{
	t_group	*tmp;
	int		hd_num;

	hd_num = 0;
	tmp = shell->groups;
	while (tmp)
	{
		if (tmp->type == REDIR_HD)
		{
			create_heredoc(shell, tmp->next->word, hd_num);
			hd_num++;
		}
		tmp = tmp->next;
	}
}
