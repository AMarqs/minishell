/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:52:31 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/19 14:52:57 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*subs_var(t_shell *shell, t_token **tokens, char *old)
{
	char	*str;
	char	*aux;
	int		len;
	t_token	*tmp;
	t_env	*aux_env;
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
			free_all_malloc(shell);
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
		free_all_malloc(shell);
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
				free_all_malloc(shell);
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
			free_all_malloc(shell);
		}
		return (str);
	}
	return (NULL);
}
