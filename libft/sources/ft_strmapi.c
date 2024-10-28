/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 18:07:45 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 20:00:20 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Applies the function ’f’ to each character of the string ’s’ to create
 * a new string resulting from successive applications of ’f’.
 *		- s: The string to map.
 *		- f: The function to apply to each character.
 * Returns the string created from the successive applications of ’f’, 
 * or NULL if the allocation fails.
 */

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	x;
	char	*str;
	size_t	i;

	x = ft_strlen(s);
	str = (char *)malloc(sizeof(char) * (x + 1));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < x)
		str[i] = f(i, s[i]);
	str[i] = '\0';
	return (str);
}
