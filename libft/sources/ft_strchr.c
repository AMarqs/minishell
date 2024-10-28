/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:07:52 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:49:42 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Locates the first occurrence of c (converted to a char) in the string pointed
 * to by s. The terminating null character is considered
 * to be part of the string.
 *		- s: The string to be analyzed.
 *		- c: The character to search for.
 * Returns a pointer to the located character,
 * or NULL if the character does not appear in the string.
 */

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	ch;
	char	*str;

	ch = (char) c;
	str = (char *)s;
	i = -1;
	while (s[++i])
		if (s[i] == ch)
			return (str + i);
	if (ch == 0)
		return (str + i);
	return (NULL);
}
