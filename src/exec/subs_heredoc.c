/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subs_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 17:39:15 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/20 18:48:53 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_prev_status(t_shell *shell, int fd)
{
	char	*exit_status;

	exit_status = ft_itoa(shell->prev_status);
	if (!exit_status)
	{
		close(fd);
		free_all_malloc(shell);
	}
	ft_putstr_fd(exit_status, fd);
}

void	print_env_var(t_shell *shell, char *line, int *i, int fd)
{
	int		len;
	char	*var;
	char	*tmp;

	len = 0;
	if (line[*i] && (ft_isalpha(line[*i]) || line[*i + 1] == '_'))
	{
		while (line[*i] && (ft_isalnum(line[*i])
				|| line[*i] == '_'))
		{
			len++;
			(*i)++;
		}
		var = ft_substr(line, (*i - len), len);
		if (!var)
		{
			close(fd);
			free_all_malloc(shell);
		}
		(*i)--;
		tmp = search_env(shell, var);
		free(var);
		if (tmp)
			ft_putstr_fd(tmp, fd);
	}
}

void	print_var(t_shell *shell, char *line, int *i, int fd)
{
	if (line[++(*i)] == '?')
		print_prev_status(shell, fd);
	else
		print_env_var(shell, line, i, fd);
}

void	subs_hd(t_shell *shell, char *line, int fd)
{
	int	i;

	i = 0;
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
				print_var(shell, line, &i, fd);
		}
		else
			ft_putchar_fd(line[i], fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
}
