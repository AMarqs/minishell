/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_delimiter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:13:08 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/28 18:13:56 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_delimeter(t_shell *shell)
{
	t_group	*tmp;
	int		type;

	tmp = shell->groups;
	while (tmp)
	{
		type = tmp->type;
		tmp = tmp->next;
	}
	if (type == REDIR_HD)
		return (1);
	else
		return (0);
}

char	*get_del_var(t_token **tokens)
{
	int				len;
	enum e_token	type;
	t_token			*tmp;
	char			*aux;

	len = 0;
	tmp = *tokens;
	type = tmp->type;
	while (tmp && tmp->type == type)
	{
		len++;
		tmp = tmp->next;
	}
	tmp = *tokens;
	aux = malloc(sizeof(char) * (len + 1));
	return (aux);
}

char	*subs_delimiter(t_shell *shell, t_token **tokens, char *str)
{
	char			*aux;
	char			*str2;
	int				len;
	enum e_token	type;

	type = (*tokens)->type;
	aux = get_del_var(tokens);
	if (!aux)
	{
		free(str);
		free_all_malloc(shell);
	}
	len = 0;
	while (*tokens && (*tokens)->type == type)
	{
		aux[len++] = (*tokens)->value;
		*tokens = (*tokens)->next;
	}
	aux[len] = '\0';
	str2 = better_strjoin(str, aux);
	free(aux);
	free(str);
	if (!str2)
		free_all_malloc(shell);
	return (str2);
}
