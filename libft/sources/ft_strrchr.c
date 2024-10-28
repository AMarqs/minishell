/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:30:49 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:54:29 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Locates the last occurrence of c (converted to a char)
 * in the string pointed to by s.
 *		- s: The string to be searched.
 *		- c: The character to be located.
 * Returns a pointer to the located character,
 * or NULL if the character does not appear in the string.
 */

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	ch;
	char	*str;

	str = (char *)s;
	ch = (char)c;
	i = ft_strlen(s) + 1;
	while (--i >= 0)
		if (s[i] == ch)
			return (str + i);
	return (NULL);
}
