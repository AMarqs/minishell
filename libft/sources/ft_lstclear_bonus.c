/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:15:20 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:30:13 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Deletes and frees the memory of the given element and every
 * successor of that element, using the function ’del’ and free(3).
 * Finally, the pointer to the list must be set to NULL.
 *		- lst: The address of a pointer to an element.
 *		- del: The address of the function used to delete 
 *				the content of said element.
 */

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*first;
	t_list	*new;

	if (lst)
	{
		while (*lst)
		{
			first = *lst;
			new = (*lst)->next;
			if (first->content && del)
				del((first)->content);
			free(first);
			*lst = new;
		}
		*lst = NULL;
	}
}
