/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 14:34:03 by albmarqu          #+#    #+#             */
/*   Updated: 2024/12/11 12:31:42 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	syntax_error_newline(t_shell *shell)
{
	char	*str;

	str = "minishell: syntax error near unexpected token `newline'\n";
	ft_putstr_fd(str, 2);
	shell->exit_status = 2;
}

void	syntax_error(t_shell *shell, char *word)
{
	char	*str;
	char	*aux;

	str = ft_strjoin("minishell: syntax error near unexpected token `", word);
	if (!str)
		free_all_malloc(shell);
	aux = ft_strjoin(str, "'\n");
	free(str);
	if (!aux)
		free_all_malloc(shell);
	ft_putstr_fd(aux, 2);
	free(aux);
	shell->exit_status = 2;
}

char	*fill_ambiguous(t_token *tmp, char *str)
{
	int	i;

	i = 0;
	while (tmp->type != CHAR && tmp->type != ENV_VAR && tmp->type != ENV_VAR_Q)
		tmp = tmp->next;
	while (tmp && (tmp->type == CHAR || tmp->type == ENV_VAR
			|| tmp->type == ENV_VAR_Q))
	{
		str[i++] = tmp->value;
		tmp = tmp->next;
	}
	str[i] = '\0';
	return (str);
}

char	*print_ambiguous(t_shell *shell, t_token *token)
{
	t_token	*tmp;
	char	*str;
	int		i;

	i = 0;
	tmp = token;
	while (tmp->type != CHAR && tmp->type != ENV_VAR && tmp->type != ENV_VAR_Q)
		tmp = tmp->next;
	while (tmp && (tmp->type == CHAR || tmp->type == ENV_VAR
			|| tmp->type == ENV_VAR_Q))
	{
		i++;
		tmp = tmp->next;
	}
	tmp = token;
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		free_all_malloc(shell);
	str = fill_ambiguous(tmp, str);
	return (str);
}

void	ambiguous_error(t_shell *shell, t_group *tmp)
{
	char	*str;
	char	*aux;

	aux = print_ambiguous(shell, tmp->first_token);
	str = ft_strjoin("minishell: ", aux);
	free(aux);
	if (!str)
		free_all_malloc(shell);
	aux = ft_strjoin(str, ": ambiguous redirect\n");
	free(str);
	if (!aux)
		free_all_malloc(shell);
	ft_putstr_fd(aux, 2);
	free(aux);
	shell->exit_status = 1;
}
