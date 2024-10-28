/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 20:40:00 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:51:10 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Copies up to dstsize - 1 characters from the string src to dst,
 * NUL-terminating the result if dstsize is not 0.
 *		- dst: The destination string.
 *		- src: The source string.
 *		- dstsize: The size of the destination buffer.
 * Returns the total length of the string it tried to create.
 */

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	if (!dstsize)
		return (len);
	i = -1;
	while (src[++i] && --dstsize)
		dst[i] = src[i];
	dst[i] = '\0';
	return (len);
}
