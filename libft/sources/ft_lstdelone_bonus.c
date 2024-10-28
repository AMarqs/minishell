/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:10:21 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/02 19:30:03 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Takes as a parameter an element and frees the memory of the element’s
 * content using the function ’del’ given as a parameter, then frees the element.
 * The memory of ’next’ must not be freed.
 *		- lst: The element to free.
 *		- del: The address of the function used to delete
 *				the content of the element.
 */

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		if (lst->content && del)
			del(lst->content);
		free(lst);
	}
}
