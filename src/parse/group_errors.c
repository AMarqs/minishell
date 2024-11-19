/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:34:03 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/19 15:02:28 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	syntax_error_newline(t_shell *shell)
{
	ft_putstr_fd("minishell: syntax error near unexpected ", 2);
	ft_putstr_fd("token `newline'\n", 2);
	shell->exit_status = 2;
}

void	syntax_error(t_shell *shell, char *word)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(word, 2);
	ft_putstr_fd("'\n", 2);
	shell->exit_status = 2;
}

void	print_ambiguous(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp->type != CHAR && tmp->type != ENV_VAR && tmp->type != ENV_VAR_Q)
		tmp = tmp->next;
	while (tmp && (tmp->type == CHAR || tmp->type == ENV_VAR
			|| tmp->type == ENV_VAR_Q))
	{
		ft_putchar_fd(tmp->value, 2);
		tmp = tmp->next;
	}
}

void	ambiguous_error(t_shell *shell, t_group *tmp)
{
	ft_putstr_fd("minishell: ", 2);
	print_ambiguous(tmp->first_token);
	ft_putstr_fd(": ambiguous redirect\n", 2);
	shell->exit_status = 1;
}
