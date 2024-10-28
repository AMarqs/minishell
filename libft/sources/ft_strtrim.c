/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:55:31 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:53:48 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
 * specified in ’set’ removed from the beginning and the end of the string.
 *		- s1: The string to be trimmed.
 *		- set: The reference set of characters to trim.
 * Returns the trimmed string or NULL if the allocation fails.
 */


/* Checks if a character is in a set of characters. */

static int	isset(const char c, const char *set)
{
	size_t	i;

	i = 0;
	while (set[i])
		if (set[i++] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	k;
	char	*str;

	if (!s1)
		return (NULL);
	i = 0;
	while (s1[i] && (isset(s1[i], set) == 1))
		i++;
	j = ft_strlen(s1);
	while (j > i && (isset(s1[j - 1], set) == 1))
		j--;
	str = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!str)
		return (NULL);
	k = 0;
	while (k + i < j)
	{
		str[k] = s1[k + i];
		k++;
	}
	str[k] = '\0';
	return (str);
}
