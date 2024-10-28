/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:02:43 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:52:22 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Converts a lower-case letter to the corresponding upper-case letter.
 *		- c: The character to be converted.
 * Returns the corresponding upper-case letter if c is a lower-case letter.
 * Returns the argument c if c is not a lower-case letter.
 */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		c -= 32;
	return (c);
}
