/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:41:11 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/18 20:23:00 by albmarqu         ###   ########.fr       */
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

// Global Variable
extern volatile sig_atomic_t	g_signal;

// DEFINES structures

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
	char			*file;
	struct s_token	*first_token;
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
void		malloc_error(void);
void		free_array(char **array);
void		*free_groups(t_group *group);
void		*free_tokens(t_token *token);
int			save_restore_fds(int i);
void		print_groups(t_group *group); ///////// BORRAR FUNCION
void		print_array(char **array); ///////// BORRAR FUNCION
char		*search_env(t_shell *shell, char *key);

// BULT-INS

// cd.c
void		args_cd_error(t_shell *shell);
void		file_cd_error(t_shell *shell, char *file, char *oldpwd);
void		update_pwd(t_shell *shell, char *oldpwd);
void		cd(t_shell *shell, char **args);

// echo.c
int			is_n_flag(char *arg);
void		ft_echo(t_shell *shell, char **args);

// env.c
void		env(t_shell *shell);

// exit.c
void		num_exit_error(t_shell *shell, char *arg);
void		args_exit_error(t_shell *shell);
void		exit_shell(t_shell *shell, char **args);

// export_utils.c
void		export_error(t_shell *shell, char *arg);
void		ft_swap(char **a, char **b);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_split_var(t_env *new, char *value);
// export_env.c
void		node_dup(t_env **envp, t_env *new, t_env **tmp, t_env **tmp2);
t_env		*envp_dup(t_env *envp);
void		order_dup(t_env *sorted, t_env *first, int len);
void		print_node(t_env *tmp);
int			order_env(t_shell *shell);
// export.c
void		add_one_envp(t_env *tmp, t_env *new);
void		add_envp(t_shell *shell, t_env *new);
int			check_export(char *args);
int			export(t_shell *shell, char **args);

// pwd.c
void		pwd(t_shell *shell);

// unset.c
void		unset_node(t_shell *shell, char *arg);
void		unset(t_shell *shell, char **args);

// EXECUTION

// environment.c
t_env		*environ(t_shell *shell, char **envp);
t_env		*env_values(char *env);

// redirections.c
void		input_redirection(t_shell *shell, char *file);
void		output_redirection(t_shell *shell, char *file);
void		append_redirection(t_shell *shell, char *file);
void		heredoc_redirection(t_shell *shell, char *doc);
void		handle_redirections(t_shell *shell, t_group *group);

// get_stuff.c
char		**get_args(t_group *groups);
char		**get_envp(t_shell *shell);
char		*get_path(t_shell *shell, char **env, char *cmd);

// heredoc.c
int			count_hd(t_group *groups);
void		subs_hd(t_shell *shell, char *line, int fd);
void		create_heredoc(t_shell *shell, t_group *group, int hd_num);
void		read_heredocs(t_shell *shell);

// SRC

// utils.c
char		**ft_split_env(char *str, char del);
int			ft_isspace(char c);

// SIGNALS

// signal_init.c
void		init_signal(void);
void		init_signal_hd(void);
void		init_signal_quit(void);

// signal_handler.c
void		signal_handler(int signal);
void		signal_hd(int signal);
void		signal_quit(int signal);

// signal_utils.c
void		disable_echoctl(void);

// ERRORS AND FREES

// errors.c
void		malloc_error(void);

// frees.c
void		free_array(char **array);
void		free_heredocs(t_shell *shell);
void		*free_tokens(t_token *token);
void		*free_groups(t_group *group);
void		free_all(t_shell *shell);

#endif
