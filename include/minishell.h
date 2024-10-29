/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:41:11 by glopez-c          #+#    #+#             */
/*   Updated: 2024/10/29 19:29:30 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/wait.h>

enum e_token
{
	NULLCHAR,
	CHAR,
	BLANK,
	CHAR_PIPE,
	CHAR_IN,
	CHAR_OUT,
	S_QUOTE,
	D_QUOTE,
	ENV_VAR
};

enum e_words
{
	CMD,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HD,
	REDIR_APPEND
};

typedef struct s_token
{
	enum e_token	type;
	char			value;
	struct s_token	*next;
}					t_token;

typedef struct s_group
{
	enum e_words	type;
	char			*word;
	struct s_group	*next;
}					t_group;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell
{
	t_env		*envp;
	char		**path;
	char		*line;
	int			exit_status;
	t_token		*tokens;
	t_group		*groups;
}				t_shell;


void		parse_line(t_shell *shell);
void		group_tokens(t_shell *shell);

#endif
