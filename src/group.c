/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:10:28 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/15 18:35:36 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"	

t_group	*new_group(void)
{
	t_group	*group;

	group = malloc(sizeof(t_group));
	if (!group)
		return (NULL);
	group->next = NULL;
	group->word = NULL;
	group->is_var = 0;
	group->file = NULL;
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

char	*subs_var(t_shell *shell, t_token **tokens, char *old)
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
		str = ft_itoa(shell->prev_status);
		if (!str)
		{
			free(old);
			free_all(shell);
			malloc_error();
		}
		return (str);
	}
	while (tmp && (tmp->type == ENV_VAR || tmp->type == ENV_VAR_Q)
			&& tmp->value != '$')
	{
		tmp = tmp->next;
		len++;
	}
	tmp = *tokens;
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
	{
		free(old);
		free_all(shell);
		malloc_error();
	}
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
		{
			free(str);
			str = ft_strdup(aux_env->value);
			if (!str)
			{
				free(old);
				free_all(shell);
				malloc_error();
			}
			return (str);
		}
		aux_env = aux_env->next;
	}
	free(str);
	if (type == ENV_VAR_Q)
	{
		str = ft_strdup("");
		if (!str)
		{
			free(old);
			free_all(shell);
			malloc_error();
		}
		return (str);
	}
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
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

int	add_args_group(t_shell *shell, char *str, int is_var)
{
	t_group	*tmp;
	t_group	*new;

	tmp = shell->groups;
	new = new_group();
	if (!new)
		return (0);
	new->word = str;
	new->type = ARG;
	new->is_var = is_var;
	if (!shell->groups)
	{
		shell->groups = new;
		return (1);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (1);
}

char	*space_split(t_shell *shell, char *str, char *new, int *is_var)
{
	int		i;
	int		j;
	char	*aux;
	char	*aux2;
	
	i = 0;
	while (new[i])
	{
		j = i;
		while (new[i] && !ft_isspace(new[i]))
			i++;
		if (i > j)
		{
			aux = ft_substr(new, j, i - j);
			if (!aux)
			{
				free(str);
				free(new);
				free_all(shell);
				malloc_error();
			}
			aux2 = better_strjoin(str, aux);
			free(aux);
			free(str);
			str = aux2;
			if (!str)
			{
				free(new);
				free_all(shell);
				malloc_error();
			}
		}
		if (new[i] && ft_isspace(new[i]) && str)
		{
			if (!add_args_group(shell, str, 1))
			{
				free(new);
				free(str);
				free_all(shell);
				malloc_error();
			}
			free(str);
			str = NULL;
			*is_var = 1;
		}
		if (new[i])
			i++;
	}
	if (!str)
		*is_var = 0;
	if (new[i - 1] == ' ')
		*is_var = 1;
	return (str);
}

t_token	*group_chars(t_shell *shell, t_token *tokens)
{
	t_token	*tmp;
	char	*str;
	char	*str2;
	char	aux[2];
	char	*aux2;
	int		is_var;

	tmp = tokens;
	str = NULL;
	is_var = 0;
	while (tmp && (tmp->type == CHAR || tmp->type == ENV_VAR
			|| tmp->type == ENV_VAR_Q || tmp->type == EMPTY))
	{
		while (tmp && tmp->type == CHAR)
		{
			aux[0]= tmp->value;
			aux[1] = '\0';
			str2 = better_strjoin(str, aux);
			if (!str2)
			{
				free(str);
				free_all(shell);
				malloc_error();
			}
			free(str);
			str = str2;
			tmp = tmp->next;
		}
		if (tmp && tmp->type == ENV_VAR_Q)
		{
			aux2 = subs_var(shell, &tmp, str);
			if (aux2)
			{
				str2 = better_strjoin(str, aux2);
				free(aux2);
				if (!str2)
				{
					free(str);
					free_all(shell);
					malloc_error();
				}
				free(str);
				str = str2;
			}
		}
		if (tmp && tmp->type == ENV_VAR)
		{
			aux2 = subs_var(shell, &tmp, str);
			if (aux2)
			{
				str = space_split(shell, str, aux2, &is_var);
			}
			free(aux2);
		}
		if (tmp && tmp->type == EMPTY)
		{
			str2 = better_strjoin(str, "");
			free(str);
			if (!str2)
			{
				free_all(shell);
				malloc_error();
			}
			str = str2;
			tmp = tmp->next;
		}
	}
	tokens = tmp;
	if (!str)
		return (tokens);
	if (!add_args_group(shell, str, is_var))
	{
		free(str);
		free_all(shell);
		malloc_error();
	}
	return (tokens);
}

t_token	*group_pipe(t_shell *shell, t_token *tokens)
{
	t_group	*new;
	t_token	*tmp;
	int 	i;

	new = new_group();
	if (!new)
	{
		free_all(shell);
		malloc_error();
	}
	add_group(shell, new);
	tmp = tokens;
	i = 0;
	tmp = tmp->next;
	while (tmp && tmp->type != CHAR_PIPE)
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
		if (!new->word)
		{
			free_all(shell);
			malloc_error();
		}
	}
	else
	{
		new->type = PIPE;
		new->word = ft_strdup("|");
		if (!new->word)
		{
			free_all(shell);
			malloc_error();
		}
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
	{
		free_all(shell);
		malloc_error();
	}
	add_group(shell, new);
	new->type = REDIR_IN;
	new->word = ft_strdup("<"); // se puede quitar ???
	if (!new->word)
	{
		free_all(shell);
		malloc_error();
	}
	new->first_token = tmp;
	if (tmp->next && tmp->next->type == CHAR_IN)
	{
		new->type = REDIR_HD;
		free(new->word);
		new->word = ft_strdup("<<"); // se puede quitar ???
		if (!new->word)
		{
			free_all(shell);
			malloc_error();
		}
		tmp = tmp->next;
	}
	tmp = tmp->next;
	aux = tmp;
	while (tmp)
	{
		if (tmp->type == CHAR || tmp->type == ENV_VAR || tmp->type == ENV_VAR_Q)
			ok = 1;
		else if (tmp->type != BLANK && ok == 0)
			shell->exit_status = 2;
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
	{
		free_all(shell);
		malloc_error();
	}
	add_group(shell, new);
	new->type = REDIR_OUT;
	new->word = ft_strdup(">"); // se puede quitar
	if (!new->word)
	{
		free_all(shell);
		malloc_error();
	}
	new->first_token = tmp;
	if (tmp->next && tmp->next->type == CHAR_OUT)
	{
		new->type = REDIR_APPEND;
		free(new->word);
		new->word = ft_strdup(">>"); // se puede quitar
		if (!new->word)
		{
			free_all(shell);
			malloc_error();
		}
		tmp = tmp->next;
	}
	tmp = tmp->next;
	aux = tmp;
	while (tmp)
	{
		if (tmp->type == CHAR || tmp->type == ENV_VAR || tmp->type == ENV_VAR_Q)
			ok = 1;
		else if (tmp->type != BLANK && ok == 0)
			shell->exit_status = 2;
		tmp = tmp->next;
	}
	tokens = aux;
	return (tokens);
}

void	print_ambiguous(t_token *token)
{
	t_token	*tmp;
	
	tmp = token;
	while (tmp->type != CHAR && tmp->type != ENV_VAR && tmp->type != ENV_VAR_Q)
		tmp = tmp->next;
	while (tmp && (tmp->type == CHAR || tmp->type == ENV_VAR || tmp->type == ENV_VAR_Q))
	{
		ft_putchar_fd(tmp->value, 2);
		tmp = tmp->next;
	}
}

void	syntax_check(t_shell *shell)
{
	t_group	*tmp;
	
	tmp = shell->groups;
	if (tmp->type == PIPE)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		shell->exit_status = 2;
		return ;
	}
	while (tmp)
	{
		if (tmp->type == REDIR_APPEND || tmp->type == REDIR_HD
		|| tmp->type == REDIR_IN || tmp->type == REDIR_OUT)
		{
			if (!tmp->next)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
				shell->exit_status = 2;
				break ;
			}
			else if (tmp->next->type != ARG)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				ft_putstr_fd(tmp->next->word, 2);
				ft_putstr_fd("'\n", 2);
				shell->exit_status = 2;
				break ;
			}
			else if (tmp->next->is_var && tmp->next->next && tmp->next->next->is_var)
			{
				ft_putstr_fd("minishell: ", 2);
				print_ambiguous(tmp->first_token);
				ft_putstr_fd(": ambiguous redirect\n", 2);
				shell->exit_status = 1;
			}
			else
				tmp->next->type = FILENAME;
		}
		else if (tmp->type == PIPE)
		{
			if (!tmp->next)			
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
				shell->exit_status = 2;
				break ;
			}
			else if (tmp->next->type == PIPE)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
				ft_putstr_fd(tmp->next->word, 2);
				ft_putstr_fd("'\n", 2);
				shell->exit_status = 2;
				break ;
			}
		}
		tmp = tmp->next;
	}	
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
	if (shell->groups)
	{
		syntax_check(shell);
		find_cmds(shell);
	}
}
