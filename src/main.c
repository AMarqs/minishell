/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:41:17 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/15 18:26:07 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

volatile sig_atomic_t	g_signal;

int	event_hook_readline(void)
{
	return (0);
}

void	print_array(char **array) /////// BORRAR FUNCION
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("array[%d]: %s\n", i, array[i]);
		fflush(stdout);
		i++;
	}
}

void	print_tokens(t_token *tokens) /////// BORRAR FUNCION
{
	t_token	*tmp;

	tmp = tokens;
	while (tmp)
	{
		printf("token_type: %d, value: %c\n", tmp->type, tmp->value);
		fflush(stdout);
		tmp = tmp->next;
	}
}

void	print_groups(t_group *groups) /////// BORRAR FUNCION
{
	t_group	*tmp;

	tmp = groups;
	if (!tmp)
		write(1, "groups is NULL\n", 15);
	while (tmp)
	{
		printf("group_type: %d, word: %s is_var: %d\n", tmp->type, tmp->word, tmp->is_var);
		fflush(stdout);
		tmp = tmp->next;
	}
}

t_env	*env_values(char *env)
{
	t_env	*new;
	char 	**tmp;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	tmp = ft_split_env(env, '=');
	if (!tmp)
	{
		free(new);
		return (NULL);
	}
	new->key = tmp[0];
	new->value = ft_strdup(getenv(new->key));
	if (!new->value)
	{
		if (tmp[1])
			free(tmp[1]);
		free(tmp[0]);
		free(tmp);
		free(new);
		return (NULL);
	}
	new->next = NULL;
	if (tmp[1])
		free(tmp[1]);
	free (tmp);
	return (new);
}

t_env	*environ(t_shell *shell, char **envp)
{
	t_env	*new;
	t_env	*tmp;
	int		i;
	
	i = 1;
	if (!envp || envp[0] == NULL)
		return (NULL);
	new = env_values(envp[0]);
	if (!new)
	{
		free(shell);
		return (NULL);		
	}
	tmp = new;
	while(envp[i])
	{
		new->next = env_values(envp[i]);
		if (!new->next)
		{
			free_all(shell);  /// Liberar new, new->key, new->value (para todo lo anterior), y shell
			/// Mensaje de error y exit
			return (NULL);
		}
		new = new->next;
		i++;
	}
	new = tmp;
	return (new);
}

char	*search_env(t_shell *shell, char *key)
{
	t_env	*tmp;

	tmp = shell->envp;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_shell	*shell;
	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		return (1);  /////////////////////// ADD ERROR FUNCTION
	}
	//shell->path = get_path(shell);
	//shell->path = NULL;
	shell->envp = environ(shell, envp);
	shell->tokens = NULL;
	shell->groups = NULL;
	shell->line = NULL;
	shell->exit_status = 0;
	init_signal();
	disable_echoctl();
	rl_event_hook = event_hook_readline;
	char *pwd[2];
	char *oldpwd[2];
	if (!search_env(shell, "PWD"))
	{
		char *cwd;
		cwd = getcwd(NULL, 0);
		pwd[0] = ft_strjoin("PWD=", cwd);
		if (!pwd[0])
		{
			free(cwd);
			free_all(shell); // envp y shell
			malloc_error();
		}
		pwd[1] = NULL;
		free(cwd);
		if (!export(shell, pwd))
		{
			free(pwd[0]);
			free_all(shell); // envp y shell
			malloc_error();
		}
		free(pwd[0]);
	}
	if (!search_env(shell, "OLDPWD"))
	{
		oldpwd[0] = "OLDPWD";
		oldpwd[1] = NULL;
		if (!export(shell, oldpwd))
		{
			free_all(shell); // envp y shell
			malloc_error();
		}
	}
	if (!search_env(shell, "PATH"))
	{
		char *path[2];
		path[0] = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
		path[1] = NULL;
		if (!export(shell, path))
		{
			free_all(shell); // envp y shell
			malloc_error();
		}
	}
	char *shlvl[2];
	if (!search_env(shell, "SHLVL"))
	{
		shlvl[0] = "SHLVL=1";
		shlvl[1] = NULL;
		if (!export(shell, shlvl))
		{
			free_all(shell); // envp y shell
			malloc_error();
		}
	}
	else
	{
		int i = ft_atoi(search_env(shell, "SHLVL"));
		if (i < -1 || i == INT_MAX)
			i = 0;
		else
			i++;
		char *aux = ft_itoa(i);
		if (i > 2000000)
		{
			i = 1;
			ft_putstr_fd("minishell: warning: shell level (", 2);
			ft_putstr_fd(aux, 2);
			ft_putstr_fd(") too high, resetting to 1\n", 2);
		}
		free(aux);
		aux = ft_itoa(i);
		if (!aux)
		{
			free_all(shell); // envp y shell
			malloc_error();
		}
		shlvl[0] = ft_strjoin("SHLVL=", aux);
		free(aux);
		if (!shlvl[0])
		{
			free_all(shell); // envp y shell
			malloc_error();
		}
		shlvl[1] = NULL;
		if (!export(shell, shlvl))
		{
			free(shlvl[0]);
			free_all(shell); // envp y shell
			malloc_error();
		}
		free(shlvl[0]);
	}
	// if (!search_env(shell, "_"))
	// {
	// 	if (search_env(shell, "SHELL"))
	// 	{
	// 		char *underscore[2];
	// 		underscore[0] = ft_strjoin("_=", search_env(shell, "SHELL"));
	// 		underscore[1] = NULL;
	// 		export(shell, underscore);
	// 	}
	// 	else
	// 	{
	// 		char *underscore[2];
	// 		underscore[0] = "_=./minishell";
	// 		underscore[1] = NULL;
	// 		export(shell, underscore);
	// 	}
	// }

	if (argc >=2 && ft_strcmp(argv[1], "-c") == 0)
	{
		shell->path = NULL;
		char *line2 = ft_substr(argv[2], 0, ft_strlen(argv[2]) - 1);
		if (!line2)
		{
			free_all(shell);
			malloc_error();
		}
		shell->line = line2;
		if (!line2)
			return (shell->exit_status);
		if (line2[0] != '\0')
		{
			shell->exit_status = 0;
			parse_line(shell);
			group_tokens(shell);
			//print_groups(shell->groups);
			if (shell->groups && shell->exit_status == 0)
				exec_everything(shell);
			shell->prev_status = shell->exit_status;
			//free_all(shell);
		}
	}
	else
	{
		while (1)
		{
			shell->path = NULL;
			line = readline("minishell$ ");
			if (!line)
				break ;
			shell->line = line;
			if (line[0] != '\0')
			{
				shell->exit_status = 0;
				add_history(line);
				parse_line(shell);
				group_tokens(shell);
				//print_groups(shell->groups);
				//printf("exit_status: %d\n", shell->exit_status);
				if (shell->groups && shell->exit_status == 0)
					exec_everything(shell);
				shell->prev_status = shell->exit_status;
				//free_all(shell);
			}
			free(line);
			shell->line = NULL;
			shell->groups = free_groups(shell->groups);
			shell->tokens = free_tokens(shell->tokens);
		}
	}
	// rl_clear_history();
	int i = shell->exit_status;
	free_all(shell);
	return (i);
}

// /home/ubuntu/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin