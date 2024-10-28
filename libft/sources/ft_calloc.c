/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 12:06:40 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:19:37 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates memory for an array of nmemb elements of size bytes each and
 * returns a pointer to the allocated memory. The memory is set to zero.
 *		- count: The number of elements to allocate.
 *		- size: The size of each element.
 * Returns the allocated memory or NULL if an error ocurred.
 */

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*s;
	size_t			i;

	s = (unsigned char *)malloc(size * count);
	if (!s)
		return (NULL);
	i = -1;
	while (++i < count * size)
		s[i] = 0;
	return (s);
}
