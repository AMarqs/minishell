/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:44:53 by albmarqu          #+#    #+#             */
/*   Updated: 2024/11/29 19:40:15 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	malloc_error(void)
{
	ft_putstr_fd("Fatal error: malloc: memory allocation error\n", 2);
	exit(1);
}

void	free_all_malloc(t_shell *shell)
{
	free_all(shell);
	malloc_error();
}

void	hd_error(t_shell *shell, char *word)
{
	char	*str;
	char	*aux;

	str = "minishell: warning: here-document ";
	str = ft_strjoin(str, "delimited by end-of-file (wanted `");
	if (!str)
		free_all_malloc(shell);
	aux = ft_strjoin(str, word);
	free(str);
	if (!aux)
		free_all_malloc(shell);
	str = ft_strjoin(aux, "')\n");
	free(aux);
	if (!str)
		free_all_malloc(shell);
	ft_putstr_fd(str, 2);
	free(str);
}

void	perror_error(t_shell *shell, char *word)
{
	char	*str;
	char	*aux;

	str = ft_strjoin("minishell: ", word);
	if (!str)
		free_all_malloc(shell);
	aux = ft_strjoin(str, ": ");
	free(str);
	if (!aux)
		free_all_malloc(shell);
	str = ft_strjoin(aux, strerror(errno));
	free(aux);
	if (!str)
		free_all_malloc(shell);
	ft_putstr_fd(str, 2);
	free(str);
	shell->exit_status = 1;
}

char	*get_cd_error(char *file)
{
	char	*str;

	if (access(file, F_OK))
		str = ": No such file or directory\n";
	else if (!is_directory(file))
		str = ": Not a directory\n";
	else
		str = ": Permission denied\n";
	return (str);
}
