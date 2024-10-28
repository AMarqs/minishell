/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:32:24 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 20:29:43 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Iterates the list ’lst’ and applies the function ’f’ to the content of
 * each element. Creates a new list resulting of the successive applications
 * of the function ’f’. The ’del’ function is used to delete the content of an
 * element if needed.
 *		- lst: The address of a pointer to the first element of a list.
 *		- f: The address of the function used to iterate on the list.
 *		- del: The address of the function used to delete the content 
 *			of an element if needed.
 * Returns the new list or NULL if the allocation fails.
 */

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*res;
	t_list	*new;
	void	*con;

	if (!lst || !(f) || !(del))
		return (NULL);
	res = NULL;
	while (lst)
	{
		con = f(lst->content);
		new = ft_lstnew(con);
		if (!new)
		{
			ft_lstclear(&res, (*del));
			del(con);
			return (NULL);
		}
		ft_lstadd_back(&res, new);
		lst = lst->next;
	}
	return (res);
}
