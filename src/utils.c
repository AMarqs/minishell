/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:40:24 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/08 12:49:33 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_split_env(char *str, char del)
{
	char	**array;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (str[i] && str[i] != del)
		i++;
	k = i;
	if (str[i] == del)
		i++;
	while (str[i++])
		j++;
	if (j)
		array = malloc(sizeof(char *) * (3));
	else
		array = malloc(sizeof(char *) * (2));
	if (!array)
		return (NULL);
	array[0] = ft_substr(str, 0, k);
	if (j)
	{
		array[1] = ft_substr(str, k + 1, j);
		array[2] = NULL;
	}
	else
		array[1] = NULL;
	return (array);
}
