/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:45:03 by albmarqu          #+#    #+#             */
/*   Updated: 2024/12/13 16:36:16 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	main_tester(char **argv, t_shell *shell)
{
	char	*line2;

	shell->path = NULL;
	line2 = ft_substr(argv[2], 0, ft_strlen(argv[2]));
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
