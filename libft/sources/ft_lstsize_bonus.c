/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 22:31:44 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:38:40 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Counts the number of elements in a list.
 *		- lst: The beginning of the list.
 * Returns the number of elements in the list.
 */

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 1;
	if (!lst)
		return (i - 1);
	while (lst->next)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
