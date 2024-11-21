/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:52:31 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/21 20:36:35 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*subs_question(t_shell *shell, t_token **tokens, char *old)
{
	char	*str;

	*tokens = (*tokens)->next;
	str = ft_itoa(shell->prev_status);
	if (!str)
	{
		free(old);
		free_all_malloc(shell);
	}
	return (str);
}

void	fill_var_name(t_token **tokens, t_token *tmp, char *str)
{
	while (tmp && (tmp->type == ENV_VAR || tmp->type == ENV_VAR_Q)
		&& tmp->value != '$')
	{
		*str = tmp->value;
		tmp = tmp->next;
		str++;
	}
	*str = '\0';
	*tokens = tmp;
}

char	*get_var_name(t_shell *shell, t_token **tokens, char *old)
{
	char	*str;
	int		len;
	t_token	*tmp;

	tmp = *tokens;
	len = 0;
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
		free_all_malloc(shell);
	}
	fill_var_name(tokens, tmp, str);
	return (str);
}

char	*search_str_var(t_shell *shell, char *str, char *old)
{
	t_env			*aux_env;

	aux_env = shell->envp;
	while (aux_env)
	{
		if (ft_strcmp(aux_env->key, str) == 0)
		{
			free(str);
			if (aux_env->value == NULL)
				return (NULL);
			str = ft_strdup(aux_env->value);
			if (!str)
			{
				free(old);
				free_all_malloc(shell);
			}
			return (str);
		}
		aux_env = aux_env->next;
	}
	free(str);
	return (NULL);
}

char	*subs_var(t_shell *shell, t_token **tokens, char *old)
{
	char			*str;
	enum e_token	type;

	type = (*tokens)->type;
	*tokens = (*tokens)->next;
	if ((*tokens)->value == '?')
		return (subs_question(shell, tokens, old));
	str = get_var_name(shell, tokens, old);
	str = search_str_var(shell, str, old);
	if (str)
		return (str);
	if (type == ENV_VAR_Q)
	{
		str = ft_strdup("");
		if (!str)
		{
			free(old);
			free_all_malloc(shell);
		}
		return (str);
	}
	return (NULL);
}
