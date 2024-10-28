/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:05:15 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:52:16 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Converts an upper-case letter to the corresponding lower-case letter.
 *		- c: The character to be converted.
 * Returns the corresponding lower-case letter if c is an upper-case letter.
 * Returns the argument c if c is not an upper-case letter.
 */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		c += 32;
	return (c);
}
