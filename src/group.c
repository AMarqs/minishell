/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:10:28 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/29 14:01:53 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"	

t_group	*new_group(void)
{
	t_group	*group;

	group = malloc(sizeof(t_group));
	if (!group)
		return (NULL); /////////////////////// ADD ERROR FUNCTION
	group->next = NULL;
	return (group);
}

void	add_group(t_shell *shell, t_group *new)
{
	t_group	*tmp;

	tmp = shell->groups;
	if (!shell->groups)
	{
		shell->groups = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	*subs_var(t_shell *shell, t_token **tokens)
{
	char 	*str;
	char 	*aux;
	int		len;
	t_token	*tmp;
	t_env 	*aux_env;
	
	aux_env = shell->envp;
	tmp = *tokens;
	len = 0;
	if (tmp->value == '?')
	{
		return (ft_itoa(shell->exit_status)); ///// LEAK DE MEMORIA
	}
	while (tmp->type == ENV_VAR)
	{
		tmp = tmp->next;
		len++;
	}
	tmp = *tokens;
	str = malloc(sizeof(char) * (len + 1));
	aux = str;
	while (tmp->type == ENV_VAR)
	{
		str = tmp->value;
		tmp = tmp->next;
		str++;
	}
	str = aux;
	while (aux_env)
	{
		if (ft_strncmp(aux_env->key, str, len) == 0)
			return (aux_env->value);
		aux_env = aux_env->next;
	}
	*tokens = tmp;
	return (NULL);
}

void	group_chars(t_shell *shell, t_group *group, t_token *tokens, int *is_cmd)
{
	t_group	*new;
	t_token	*tmp;
	char	*str;

	new = new_group();
	if (!new)
		return ; /////////////////////// ADD ERROR FUNCTION
	add_group(shell, new);
	tmp = tokens;
	str = ft_strdup(&tokens->value);
	if (!str)
		return ; /////////////////////// ADD ERROR FUNCTION
	tmp = tokens->next;
	while (tokens->type == CHAR || tokens->type == ENV_VAR)
	{
		while (tmp->type == CHAR)
		{
			str = ft_strjoin(str, &tmp->value);
			if (!str)
				return ; /////////////////////// ADD ERROR FUNCTION
			tmp = tmp->next;
		}
		if (tmp->type == ENV_VAR)
		{
			str = ft_strjoin(str, subs_var(shell, &tmp));
		}
	}
	new->word = str;
	if (*is_cmd)
	{
		new->type = CMD;
		*is_cmd = 0;
	}
	else
		new->type = ARG;
	tokens = tmp;
}

void	group_pipe(t_shell *shell, t_group *group, t_token *tokens)
{
	t_group	*new;
	t_token	*tmp;
	char	*str;
	int 	i;

	new = new_group();
	if (!new)
		return ; /////////////////////// ADD ERROR FUNCTION
	add_group(shell, new);
	tmp = tokens;
	i = 0;
	tmp = tmp->next;
	while (tmp && tmp->type != CHAR_PIPE)
	{
		tmp = tmp->next;
		i++;
	}
	tmp = tokens;
	while (tmp->value == ' ')
	{
		tmp = tmp->next;
		i--;
	}
	if (i == 0)
	{
		return ; /////////////////////// ADD ERROR FUNCTION
	}
	else
	{
		new->type = PIPE;
		new->word = ft_strdup("|");
		if (!new->word)
			return ; /////////////////////// ADD ERROR FUNCTION
	}
}

void	group_tokens(t_shell *shell)
{
	t_group	*group;
	t_group	*new;
	t_token	*tokens;
	int		type;
	int		is_cmd;
	
	tokens = shell->tokens;

	// group = malloc(sizeof(t_group));
	// if (!group)
	// 	return ; /////////////////////// ADD ERROR FUNCTION

	group = NULL;
	is_cmd = 1;
	while (tokens)
	{
		while (tokens->type == BLANK)
			tokens = tokens->next;
		if (tokens->type == CHAR || tokens->type == ENV_VAR)
		{
			group_chars(shell, group, tokens, &is_cmd);
		}
		else if (tokens->type == CHAR_PIPE) // doble pipe o solo espacios detras
		{
			group_pipe(shell, group, tokens);
		}
		else if (tokens->type == CHAR_IN)  //triple redir o nada de txt o env var
		{
			
		}
		else if (tokens->type == CHAR_OUT)  //triple redir o nada de txt o env var
		{
			
		}
		tokens = tokens->next;
	}
}
