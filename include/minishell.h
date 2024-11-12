/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glopez-c <glopez-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:41:11 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/12 13:43:16 by glopez-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// LIBRARIES

// personal
# include "../libft/includes/libft.h"

// external
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <sys/wait.h>

// DEFINES

// TOKENS

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
	ENV_VAR,
	ENV_VAR_Q,
	EMPTY
};

typedef struct s_token
{
	enum e_token	type;
	char			value;
	struct s_token	*next;
}					t_token;

// GROUPS

enum e_words
{
	CMD,
	ARG,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_HD,
	REDIR_APPEND,
	FILENAME
};

typedef struct s_group
{
	enum e_words	type;
	char			*word;
	int				is_var;
	struct s_group	*next;
}					t_group;

// ENVIRONMENT

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// SHELL

typedef struct s_shell
{
	char		*line;
	char		*path;                //// BORRAR SI NO SE USA
	int			exit_status;
	int			prev_status;
	t_token		*tokens;
	t_group		*groups;
	t_env		*envp;
}				t_shell;

// PROTOTYPES

void		parse_line(t_shell *shell);
void		group_tokens(t_shell *shell);
void		exec_everything(t_shell *shell);
void		free_all(t_shell *shell);
void		free_array(char **array);
void		save_restore_fds(int i);
void		print_groups(t_group *group); ///////// BORRAR FUNCION
void		print_array(char **array); ///////// BORRAR FUNCION

// BULT-INS

// cd.c
void		cd(t_shell *shell, char **args);

// echo.c
int			is_n_flag(char *arg);
void		ft_echo(t_shell *shell, char **args);

// env.c
void		env(t_shell *shell);

// exit.c
void		exit_shell(t_shell *shell, int x, char **args);

// export.c
void		ft_swap(char **a, char **b);               // a archivo utils???
int			ft_strcmp(const char *s1, const char *s2);	// a archivo utils???
t_env		*envp_dup(t_env *envp);					// a archivo manage_env???
void		order_env(t_shell *shell);				// a archivo manage_env???
void		ft_split_var(t_env *new, char *value);		// a archivo manage_env???
void		add_envp(t_shell *shell, t_env *new);		// a archivo manage_env???
int			check_export(char *args);
void		export(t_shell *shell, char **args);

// pwd.c
void		pwd(t_shell *shell);

// unset.c
void		unset(t_shell *shell, char **args);

// EXECUTION

// environment.c
t_env		*environ(char **envp);
t_env		*env_values(char *env);

// redirections.c
void		input_redirection(t_shell *shell, char *file);
void		output_redirection(t_shell *shell, char *file);
void		append_redirection(t_shell *shell, char *file);
void		heredoc_redirection(t_shell *shell, int i);
void		handle_redirections(t_shell *shell, t_group *group);

// get_stuff.c
char		**get_args(t_group *groups);
char		**get_envp(t_env *envp);
char		*get_path(t_shell *shell, char **env, char *cmd);

// heredoc.c
int			count_hd(t_group *groups);
void		subs_hd(t_shell *shell, char *line, int fd);
void		create_heredoc(t_shell *shell, char *word, int hd_num);
void		read_heredocs(t_shell *shell);

// SRC

// utils.c

char		**ft_split_env(char *str, char del);
int			ft_isspace(char c);

#endif
