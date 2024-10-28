/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 17:34:16 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:46:12 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

/* Fills the first len bytes of the memory area pointed
 * to by b with the constant byte c.
 *		- b: The memory area to be filled.
 *		- c: The constant byte to fill the memory area with.
 *		- len: The number of bytes to be filled.
 * Returns the original value of b.
 */

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*s;
	unsigned char	ch;

	s = (unsigned char *)b;
	ch = (unsigned char)c;
	while (len > 0)
		s[--len] = ch;
	return (s);
}
