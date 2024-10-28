/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:13:11 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 20:20:31 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates and returns an array of strings obtained by splitting ’s’ using
 * the character ’c’ as a delimiter. The array must be ended by a NULL pointer.
 *		- s: The string to be split.
 *		- c: The delimiter character.
 * Returns the array of new strings resulting from the split
 * or NULL in case an allocation fails.
 */


/* Counts the number of words in a string. */
static size_t	ft_count_words(const char *str, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if ((str[i + 1] == c || !str[i + 1]) && str[i] != c)
			count += 1;
		i++;
	}
	return (count);
}

/* Writes a string until the delimiter character is found. */
static void	ft_strwrite(char *dest, char const *src, char c)
{
	size_t	i;

	i = -1;
	while (src[++i] != c && src[i])
		dest[i] = src[i];
	dest[i] = '\0';
}

/* Fills the array of strings with the words of the string. */
static int	ft_fillsplit(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			j = i;
			while (s[i] != c && s[i])
				i++;
			split[k] = (char *)malloc(sizeof(char) * (i - j + 1));
			if (!split[k])
				return (k);
			ft_strwrite(split[k], s + j, c);
			k++;
		}
	}
	return (-1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	k;
	int		j;

	k = ft_count_words(s, c);
	split = (char **)malloc((sizeof(char *)) * (k + 1));
	if (!split)
		return (NULL);
	j = ft_fillsplit(split, s, c);
	if (j > -1)
	{
		while (j--)
			free(split[j]);
		free(split);
		return (NULL);
	}
	split[k] = NULL;
	return (split);
}
