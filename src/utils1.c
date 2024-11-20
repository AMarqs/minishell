/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:40:24 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/20 13:23:58 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
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

char	*split_notspace(t_shell *shell, char *str, char *new, char *aux)
{
	char	*aux2;

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
	return (str);
}

char	*split_isspace(t_shell *shell, char *str, char *new, int *is_var)
{
	if (!add_args_group(shell, str, 1))
	{
		free(new);
		free(str);
		free_all_malloc(shell);
	}
	str = NULL;
	*is_var = 1;
	return (str);
}

char	*space_split(t_shell *shell, char *str, char *new, int *is_var)
{
	int		i;
	int		j;
	char	*aux;

	i = 0;
	while (new[i])
	{
		j = i;
		while (new[i] && !ft_isspace(new[i]))
			i++;
		if (i > j)
		{
			aux = ft_substr(new, j, i - j);
			str = split_notspace(shell, str, new, aux);
		}
		if (new[i] && ft_isspace(new[i]) && str)
			str = split_isspace(shell, str, new, is_var);
		if (new[i])
			i++;
	}
	if (!str)
		*is_var = 0;
	if (new[i - 1] == ' ')
		*is_var = 1;
	return (str);
}
