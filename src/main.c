/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:41:17 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/19 13:53:38 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal;

int	event_hook_readline(void)
{
	return (0);
}

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = malloc(sizeof(t_shell));
	if (!shell)
		malloc_error();
	shell->tokens = NULL;
	shell->groups = NULL;
	shell->line = NULL;
	shell->exit_status = 0;
	shell->envp = environ(shell, envp);
	init_signal();
	disable_echoctl();
	rl_event_hook = event_hook_readline;
	return (shell);
}

void	main_loop(t_shell *shell, char *line)
{
	shell->path = NULL;
	shell->line = line;
	if (line[0] != '\0')
	{
		shell->exit_status = 0;
		add_history(line);
		parse_line(shell);
		group_tokens(shell);
		if (shell->groups && shell->exit_status == 0)
			exec_everything(shell);
		shell->prev_status = shell->exit_status;
	}
	free(line);
	shell->line = NULL;
	shell->groups = free_groups(shell->groups);
	shell->tokens = free_tokens(shell->tokens);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	char	*line;
	int		status;

	shell = init_shell(envp);
	set_env_var(shell);
	if (argc >= 2 && ft_strcmp(argv[1], "-c") == 0)
		main_tester(argv, shell);
	else
	{
		while (1)
		{
			line = readline("minishell$ ");
			if (!line)
				break ;
			main_loop(shell, line);
		}
	}
	status = shell->exit_status;
	free_all(shell);
	return (status);
}
