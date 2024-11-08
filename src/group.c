/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:10:28 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/08 13:48:07 by glopez-c         ###   ########.fr       */
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
	// free(new); // ???
}

char	*subs_var(t_shell *shell, t_token **tokens)
{
	char 	*str;
	char 	*aux;
	int		len;
	t_token	*tmp;
	t_env 	*aux_env;
	enum e_token type;
	
	type = (*tokens)->type;
	aux_env = shell->envp;
	*tokens = (*tokens)->next;
	tmp = *tokens;
	len = 0;
	if (tmp->value == '?')
	{
		*tokens = tmp->next;
		return (ft_itoa(shell->prev_status)); ///// LEAK DE MEMORIA
	}
	while (tmp && (tmp->type == ENV_VAR || tmp->type == ENV_VAR_Q)
			&& tmp->value != '$')
	{
		tmp = tmp->next;
		len++;
	}
	tmp = *tokens;
	str = malloc(sizeof(char) * (len + 1));
	aux = str;
	while (tmp && (tmp->type == ENV_VAR || tmp->type == ENV_VAR_Q)
			&& tmp->value != '$')
	{
		*str = tmp->value;
		tmp = tmp->next;
		str++;
	}
	*str = '\0';
	str = aux;
	*tokens = tmp;
	while (aux_env)
	{
		if (ft_strcmp(aux_env->key, str) == 0)
			return (ft_strdup(aux_env->value));
		aux_env = aux_env->next;
	}
	if (type == ENV_VAR_Q)
		return (ft_strdup(""));
	return (NULL);
}

char	*better_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
		return (ft_strdup(s2));
	i = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);  /////////////////////// ADD ERROR FUNCTION
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

t_token	*group_chars(t_shell *shell, t_token *tokens)
{
	t_group	*new;
	t_token	*tmp;
	char	*str;
	char	aux[2];
	char	*aux2;

	tmp = tokens;
	str = NULL;
	while (tmp && (tmp->type == CHAR || tmp->type == ENV_VAR
			|| tmp->type == ENV_VAR_Q || tmp->type == EMPTY))
	{
		while (tmp && tmp->type == CHAR)
		{
			aux[0]= tmp->value;
			aux[1] = '\0';
			str = better_strjoin(str, aux);
			tmp = tmp->next;
		}
		if (tmp && (tmp->type == ENV_VAR || tmp->type == ENV_VAR_Q))
		{
			aux2 = subs_var(shell, &tmp);
			if (aux2)
				str = better_strjoin(str, aux2);
		}
		if (tmp && tmp->type == EMPTY)
		{
			str = better_strjoin(str, "");
			tmp = tmp->next;
		}
	}
	tokens = tmp;
	if (!str)
		return (tokens);
	new = new_group();
	if (!new)
		return (NULL); /////////////////////// ADD ERROR FUNCTION
	add_group(shell, new);
	new->word = str;
	new->type = ARG;
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
		shell->exit_status = 2;
		new->type = PIPE;
		new->word = ft_strdup("|");
		//return (NULL); /////////////////////// ADD ERROR FUNCTION
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
	if (tmp->next && tmp->next->type == CHAR_IN)
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
			shell->exit_status = 2;
			//return (NULL); /////////////////////// ADD ERROR FUNCTION
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
	if (tmp->next && tmp->next->type == CHAR_OUT)
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
			shell->exit_status = 2;
			write(1, "cositas'\n", 9);
			//return (NULL); /////////////////////// ADD ERROR FUNCTION
		}
		tmp = tmp->next;
	}
	tokens = aux;
	return (tokens);
}

void	syntax_check(t_shell *shell)
{
	t_group	*tmp;
	
	tmp = shell->groups;
	while (tmp)
	{
		if (tmp->type == REDIR_APPEND || tmp->type == REDIR_HD
		|| tmp->type == REDIR_IN || tmp->type == REDIR_OUT)
		{
			if (!tmp->next)
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				break ;
			}
			else if (tmp->next->type != ARG)
			{
				printf("minishell: syntax error near unexpected token `%s'\n %d\n", tmp->next->word, tmp->next->type);
				break ;
			}
			else
				tmp->next->type = FILENAME;
		}
		else if (tmp->type == PIPE)
		{
			if (!tmp->next)			
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				break ;
			}
			else if (tmp->next->type == PIPE)
			{
				printf("minishell: syntax error near unexpected token `%s'\n", tmp->next->word);
				break ;
			}
		}
		tmp = tmp->next;
	}
	fflush(stdout);
	
}

void	find_cmds(t_shell *shell)
{
	t_group	*tmp;
	int		is_cmd;
	
	tmp = shell->groups;
	is_cmd = 1;
	while (tmp)
	{
		if (tmp->type == ARG)
		{
			if (is_cmd)
			{
				tmp->type = CMD;
				is_cmd = 0;
			}
		}
		else if (tmp->type == PIPE)
		{
			is_cmd = 1;
		}
		tmp = tmp->next;
	}
}

void	group_tokens(t_shell *shell)
{
	t_token	*tokens;
	
	tokens = shell->tokens;
	shell->groups = NULL;
	while (tokens)
	{
		if (tokens->type == BLANK)
		{
			while (tokens && tokens->type == BLANK)
				tokens = tokens->next;
		}
		else if (tokens->type == CHAR || tokens->type == ENV_VAR
		|| tokens->type == ENV_VAR_Q || tokens->type == EMPTY)
		{
			tokens = group_chars(shell, tokens);
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
	}
	syntax_check(shell);
	find_cmds(shell);
}
