/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:10:28 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/29 20:27:21 by albmarqu         ###   ########.fr       */
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
		*str = tmp->value;
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

t_token	*group_chars(t_shell *shell, t_token *tokens, int *is_cmd)
{
	t_group	*new;
	t_token	*tmp;
	char	*str;
	char	aux[2];

	new = new_group();
	if (!new)
		return (NULL); /////////////////////// ADD ERROR FUNCTION
	add_group(shell, new);
	tmp = tokens;
	//str = ft_strdup(&tokens->value);
	str = malloc(sizeof(char) * 2);
	if (!str)
		return (NULL); /////////////////////// ADD ERROR FUNCTION
	str[0] = tokens->value;
	str[1] = '\0';
	tmp = tokens->next;
	while (tmp && (tmp->type == CHAR || tmp->type == ENV_VAR))
	{
		while (tmp && tmp->type == CHAR)
		{
			aux[0]= tmp->value;
			aux[1] = '\0';
			str = ft_strjoin(str, aux);
			if (!str)
				return (NULL); /////////////////////// ADD ERROR FUNCTION
			tmp = tmp->next;
		}
		if (tmp && tmp->type == ENV_VAR)
		{
			str = ft_strjoin(str, subs_var(shell, &tmp));
		}
		//tmp = tmp->next;
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
	return (tokens);
}

t_token	*group_pipe(t_shell *shell, t_token *tokens)
{
	t_group	*new;
	t_token	*tmp;
	int 	i;

	new = new_group();
	if (!new)
		return (NULL); /////////////////////// ADD ERROR FUNCTION
	add_group(shell, new);
	tmp = tokens;
	i = 0;
	tmp = tmp->next;
	while (tmp && tmp->type != CHAR_PIPE && tmp->type != CHAR_IN && tmp->type != CHAR_OUT)
	{
		tmp = tmp->next;
		i++;
	}
	tmp = tokens->next;
	while (tmp && tmp->type == BLANK)
	{
		tmp = tmp->next;
		i--;
	}
	if (i == 0)
	{
		return (NULL); /////////////////////// ADD ERROR FUNCTION
	}
	else
	{
		new->type = PIPE;
		new->word = ft_strdup("|");
		if (!new->word)
			return (NULL); /////////////////////// ADD ERROR FUNCTION
	}
	tokens = tmp;
	return (tokens);
}

t_token	*group_in(t_shell *shell, t_token *tokens)
{
	t_group	*new;
	t_token	*tmp;
	t_token	*aux;
	int		ok;
	
	ok = 0;
	tmp = tokens;
	new = new_group();
	if (!new)
		return (NULL); /////////////////////// ADD ERROR FUNCTION
	add_group(shell, new);
	new->type = REDIR_IN;
	new->word = ft_strdup("<"); // se puede quitar
	if (tmp->next->type == CHAR_IN)
	{
		new->type = REDIR_HD;
		new->word = ft_strdup("<<"); // se puede quitar
		tmp = tmp->next;
	}
	tmp = tmp->next;
	aux = tmp;
	while (tmp)
	{
		if (tmp->type == CHAR || tmp->type == ENV_VAR)
		{
			ok = 1;
		}
		else if (tmp->type != BLANK && ok == 0)
		{
			return (NULL); /////////////////////// ADD ERROR FUNCTION
		}
		tmp = tmp->next;
	}
	tokens = aux;
	return (tokens);
}

t_token	*group_out(t_shell *shell, t_token *tokens)
{
	t_group	*new;
	t_token	*tmp;
	t_token	*aux;
	int		ok;
	
	ok = 0;
	tmp = tokens;
	new = new_group();
	if (!new)
		return (NULL); /////////////////////// ADD ERROR FUNCTION
	add_group(shell, new);
	new->type = REDIR_OUT;
	new->word = ft_strdup(">"); // se puede quitar
	if (tmp->next->type == CHAR_OUT)
	{
		new->type = REDIR_APPEND;
		new->word = ft_strdup(">>"); // se puede quitar
		tmp = tmp->next;
	}
	tmp = tmp->next;
	aux = tmp;
	while (tmp)
	{
		if (tmp->type == CHAR || tmp->type == ENV_VAR)
		{
			ok = 1;
		}
		else if (tmp->type != BLANK && ok == 0)
		{
			return (NULL); /////////////////////// ADD ERROR FUNCTION
		}
		tmp = tmp->next;
	}
	tokens = aux;
	return (tokens);
}

void	group_tokens(t_shell *shell)
{
	t_token	*tokens;
	int		is_cmd;
	
	tokens = shell->tokens;

	// group = malloc(sizeof(t_group));
	// if (!group)
	// 	return ; /////////////////////// ADD ERROR FUNCTION

	shell->groups = NULL;
	is_cmd = 1;
	while (tokens)
	{
		if (tokens->type == BLANK)
		{
			while (tokens && tokens->type == BLANK)
				tokens = tokens->next;
		}
		else if (tokens->type == CHAR || tokens->type == ENV_VAR)
		{
			tokens = group_chars(shell, tokens, &is_cmd);
		}
		else if (tokens->type == CHAR_PIPE) // doble pipe o solo espacios detras
		{
			tokens = group_pipe(shell, tokens);
		}
		else if (tokens->type == CHAR_IN)  //triple redir o nada de txt o env var
		{
			tokens = group_in(shell, tokens);
		}
		else if (tokens->type == CHAR_OUT)  //triple redir o nada de txt o env var
		{
			tokens = group_out(shell, tokens);
		}
		//tokens = tokens->next;
	}
	
}
