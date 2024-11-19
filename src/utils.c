/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:40:24 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/19 14:39:35 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
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
				free_all_malloc(shell);
			}
			aux2 = better_strjoin(str, aux);
			free(aux);
			free(str);
			str = aux2;
			if (!str)
			{
				free(new);
				free_all_malloc(shell);
			}
		}
		if (new[i] && ft_isspace(new[i]) && str)
		{
			if (!add_args_group(shell, str, 1))
			{
				free(new);
				free(str);
				free_all_malloc(shell);
			}
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