/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 10:45:56 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:57:02 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Locates the first occurrence of the null-terminated string needle in the
 * null-terminated string haystack, where not more than len characters are
 * searched. Characters that appear after a '\0' character are not searched.
 *		- haystack: The string to be searched.
 *		- needle: The string to search for.
 *		- len: The number of characters to search.
 * Returns a pointer to the first character of the first occurrence of needle
 * in haystack, or a null pointer if needle is not part of haystack.
 */

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ret;

	ret = (char *)haystack;
	if (!needle[0])
		return (ret);
	i = -1;
	while (haystack[++i] && i < len)
	{
		j = 0;
		while (needle[j] == haystack[j + i] && i + j < len)
			if (!needle[++j])
				return (ret + i);
	}
	return (NULL);
}
