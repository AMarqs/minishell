/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:45:03 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/28 13:06:33 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	main_tester(char **argv, t_shell *shell)
{
	char	*line2;

	shell->path = NULL;
	line2 = ft_substr(argv[2], 0, ft_strlen(argv[2]) - 1); // SE COME ULTIMO CHAR
	if (!line2)
		free_all_malloc(shell);
	shell->line = line2;
	if (line2[0] != '\0')
	{
		shell->exit_status = 0;
		parse_line(shell);
		group_tokens(shell);
		if (shell->groups && shell->exit_status == 0)
			exec_everything(shell);
		shell->prev_status = shell->exit_status;
	}
}
