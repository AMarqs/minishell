/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_BORRAR.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:08:21 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/19 13:08:46 by albmarqu         ###   ########.fr       */
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