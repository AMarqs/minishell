/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:18:05 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:45:44 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copies len bytes from string src to string dst. The two strings may overlap;
 * the copy is always done in a non-destructive manner.
 *		- dst: The destination string.
 *		- src: The source string.
 *		- len: The number of bytes to copy.
 * Returns the original value of dst.
 */

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*s1;
	char	*s2;

	s1 = (char *)src;
	s2 = (char *)dst;
	i = 0;
	if (s2 == s1)
		return (s2);
	if (s2 > s1)
		while (len--)
			s2[len] = s1[len];
	else
		while (len--)
			s2[i++] = *s1++;
	return (s2);
}
