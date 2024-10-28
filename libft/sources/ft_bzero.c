/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 18:55:51 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:17:33 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Writes n zeroed bytes to the string s.
 *		- n: The number of bytes to write.
 *		- s: The pointer to the string.
*/

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}
