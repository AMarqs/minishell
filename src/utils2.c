/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 12:37:11 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/20 13:14:47 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**ft_subs_env(char **array, char *str, int j, int k)
{
	array[0] = ft_substr(str, 0, k);
	if (!array[0])
	{
		free(array);
		return (NULL);
	}
	if (j)
	{
		array[1] = ft_substr(str, k + 1, j);
		if (!array[1])
		{
			free(array[0]);
			free(array);
			return (NULL);
		}
		array[2] = NULL;
	}
	else
		array[1] = NULL;
	return (array);
}

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
	array = ft_subs_env(array, str, j, k);
	if (!array)
		return (NULL);
	return (array);
}
