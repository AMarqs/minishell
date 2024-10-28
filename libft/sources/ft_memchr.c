/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:27:03 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:41:35 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Locates the first occurrence of c (converted to an unsigned char)
 * in string s.
 *		- s: The string to be analyzed.
 *		- c: The character to be located.
 *		- n: The number of bytes to be analyzed.
 * Returns a pointer to the located character or NULL 
 * if the character does not appear in the string.
 */

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*st;
	unsigned char	ch;
	size_t			i;

	i = 0;
	st = (unsigned char *)s;
	ch = (unsigned char)c;
	while (n--)
	{
		if (st[i] == ch)
			return (st + i);
		i++;
	}
	return (NULL);
}
