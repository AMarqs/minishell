/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 11:45:13 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:17:16 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*	Converts the initial portion of the string str to int representation.
 *		- Ignores whitespaces.
 *		- Considers the sign of the number.
 *		- Stops reading when a non-digit character is found.
 *		- Returns the result multiplied by the sign.
*/

int	ft_atoi(const char *str)
{
	int		sign;
	int		result;
	size_t	i;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] >= '0' && str[i] <= '9')
		result = (result * 10) + (str[i++] - '0');
	result *= sign;
	return (result);
}
