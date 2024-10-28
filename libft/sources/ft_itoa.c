/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:11:22 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 20:33:19 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Allocates and returns a string representing the integer received as an
 * argument. Negative numbers are handled.
 *		- n: The integer to be converted.
 * Returns the string representing the integer or NULL if the allocation fails.
 */


/* Returns the number of digits in a number. */

static int	ft_nbrlen(long n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n >= 10)
	{
		i++;
		n /= 10;
	}
	return (i + 1);
}

/* Fills the string with the digits of the number. */

static void	ft_fillstrlong(char *str, long n, size_t *i)
{
	if (n >= 10)
	{
		ft_fillstrlong(str, n / 10, i);
		ft_fillstrlong(str, n % 10, i);
	}
	else
		str[(*i)++] = n + '0';
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	i;
	long	nbr;

	nbr = n;
	n = ft_nbrlen(nbr);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	i = 0;
	if (nbr < 0)
	{
		str[i++] = '-';
		nbr *= -1;
	}
	ft_fillstrlong(str, nbr, &i);
	str[n] = '\0';
	return (str);
}
