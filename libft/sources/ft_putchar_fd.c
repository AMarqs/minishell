/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 20:44:45 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:46:25 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Outputs the character ’c’ to the given file descriptor.
 *		- c: The character to output.
 *		- fd: The file descriptor on which to write.
 */

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
