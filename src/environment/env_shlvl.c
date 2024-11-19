/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_shlvl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 13:25:30 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/19 13:44:11 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	found_shlvl(t_shell *shell, int i)
{
	char	*aux;
	char	*shlvl[2];

	if (i > 2000000)
	{
		ft_putstr_fd("minishell: warning: shell level (", 2);
		ft_putnbr_fd(i, 2);
		ft_putstr_fd(") too high, resetting to 1\n", 2);
		i = 1;
	}
	aux = ft_itoa(i);
	if (!aux)
		free_all_malloc(shell);
	shlvl[0] = ft_strjoin("SHLVL=", aux);
	free(aux);
	if (!shlvl[0])
		free_all_malloc(shell);
	shlvl[1] = NULL;
	if (!export(shell, shlvl))
	{
		free(shlvl[0]);
		free_all_malloc(shell);
	}
	free(shlvl[0]);
}

void	set_shlvl(t_shell *shell)
{
	char	*shlvl[2];
	int		i;

	if (!search_env(shell, "SHLVL"))
	{
		shlvl[0] = "SHLVL=1";
		shlvl[1] = NULL;
		if (!export(shell, shlvl))
			free_all_malloc(shell);
	}
	else
	{
		i = ft_atoi(search_env(shell, "SHLVL"));
		if (i < -1 || i == INT_MAX)
			i = 0;
		else
			i++;
		found_shlvl(shell, i);
	}
}
