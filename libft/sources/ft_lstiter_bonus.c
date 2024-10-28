/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:25:52 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:36:51 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Iterates the list ’lst’ and applies the function ’f’ to the content of
 * each element.
 *		- lst: The address of a pointer to the first element of the list.
 *		- f: The address of the function used to iterate on the list.
 */

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst)
	{
		if (lst->content && f)
			f(lst->content);
		lst = lst->next;
	}
}
