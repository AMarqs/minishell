/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:41:17 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/12 18:05:38 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		return (NULL); /////////////////////// ADD ERROR FUNCTION
	tmp = ft_split_env(env, '=');
	if (!tmp)
		return (NULL); /////////////////////// ADD ERROR FUNCTION
	new->key = tmp[0];
	new->value = ft_strdup(getenv(new->key));
	new->next = NULL;
	free (tmp);
	return (new);
}

t_env	*environ(char **envp)
{
	t_env	*new;
	t_env	*tmp;
	int		i;
	
	i = 1;
	if (!envp)
		return (NULL);
	if (!envp[0])
		return (NULL);
	new = env_values(envp[0]);
	tmp = new;
	while(envp[i])
	{
		new->next = env_values(envp[i]);
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
	shell->path = NULL;
	shell->envp = environ(envp);
	char *pwd[2];
	char *oldpwd[2];
	if (!search_env(shell, "PWD"))
	{
		pwd[0] = ft_strjoin("PWD=", getcwd(NULL, 0));
		pwd[1] = NULL;
		export(shell, pwd);
	}
	if (!search_env(shell, "OLDPWD"))
	{
		oldpwd[0] = "OLDPWD";
		oldpwd[1] = NULL;
		export(shell, oldpwd);
	}
	if (!search_env(shell, "PATH"))
	{
		char *path[2];
		path[0] = "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin";
		path[1] = NULL;
		export(shell, path);
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

	
	char *shlvl[2];
	if (!search_env(shell, "SHLVL"))
	{
		shlvl[0] = "SHLVL=1";
		shlvl[1] = NULL;
		export(shell, shlvl);
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
		aux = ft_itoa(i);
		shlvl[0] = ft_strjoin("SHLVL=", aux);
		shlvl[1] = NULL;
		free(aux);
		export(shell, shlvl);
	}
	//shell->path = get_path(shell);
	shell->exit_status = 0;
	shell->tokens = NULL;
	if (argc != 1 && ft_strcmp(argv[1], "-c") == 0)
	{
		shell->path = NULL;
		char *line2 = ft_substr(argv[2], 0, ft_strlen(argv[2]) - 1);
		shell->line = line2;
		if (!line2)
			return (shell->exit_status);
		if (line2[0] != '\0')
		{
			shell->exit_status = 0;
			add_history(line2);
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
				shell->line = line;
				if (!line)
					break ;
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
			}
		}
	rl_clear_history();
	return (shell->exit_status);
	// int i = shell->exit_status;
	// free_all(shell);
	// return (i);
}

// /home/ubuntu/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin