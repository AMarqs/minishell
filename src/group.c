/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:10:28 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/28 19:30:33 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*subs_var(t_shell *shell, t_token **tokens)
{
	// METER ENTORNO EN UN ESTRUCTURA PARA PODER ACCEDER A EL FACILMENTE
}	

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
		else if (tokens->type == CHAR_PIPE) // dopble pipe o solo espacios detras
		{
			
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
