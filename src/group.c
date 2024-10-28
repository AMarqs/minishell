/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:10:28 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/28 18:26:02 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	group_tokens(t_shell *shell)
{
	t_group	*group;
	t_token	*tokens;
	
	tokens = shell->tokens;
	group = malloc(sizeof(t_group));
	if (!group)
		return ; /////////////////////// ADD ERROR FUNCTION
	while (tokens)
	{
		
	}
}
