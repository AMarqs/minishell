/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 13:26:08 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:52:10 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates (with malloc(3)) and returns a substring from the string ’s’.
 * The substring begins at index ’start’ and is of maximum size ’len’.
 *		- s: The string from which to create the substring.
 *		- start: The start index of the substring in the string ’s’.
 *		- len: The maximum length of the substring.
 * Returns the substring or NULL if the allocation fails.
 */

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	slen;
	size_t	i;

	slen = ft_strlen(s);
	if (start > slen)
	{
		str = (char *)malloc(sizeof(char) * 1);
		if (!str)
			return (NULL);
		str[0] = '\0';
	}
	else
	{
		if (len > slen - start)
			len = slen - start;
		str = (char *)malloc(sizeof(char) * (len + 1));
		if (!str)
			return (NULL);
		i = -1;
		while (++i < len)
			str[i] = s[start + i];
		str[i] = 0;
	}
	return (str);
}
