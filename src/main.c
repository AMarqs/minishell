/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:41:17 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/08 19:20:51 by glopez-c         ###   ########.fr       */
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
		printf("group_type: %d, word: %s\n", tmp->type, tmp->word);
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
	new->value = tmp[1];
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

int	main(int argc, char **argv, char **envp)
{

	if (argc > 1 || argv[1])
	{
		write(2, "Error: Invalid arguments\n", 25);
		return (1);
	}
	

	char	*line;
	t_shell	*shell;
	shell = malloc(sizeof(t_shell));
	if (!shell)
	{
		return (1);  /////////////////////// ADD ERROR FUNCTION
	}
	
	shell->envp = environ(envp);

	char *oldpwd[2];
	oldpwd[0] = "OLDPWD";
	oldpwd[1] = NULL;
	export(shell, oldpwd);
	//shell->path = get_path(shell);
	shell->exit_status = 0;
	shell->path = NULL;
	shell->tokens = NULL;
	while (1)
	{
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
			if (shell->groups)
				exec_everything(shell);
			shell->prev_status = shell->exit_status;
			//free_all(shell);
		}
		free(line);
	}
	rl_clear_history();
	// int i = shell->exit_status;
	// free_all(shell);
	// return (i);
}
