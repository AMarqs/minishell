/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: albmarqu <albmarqu@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:41:11 by glopez-c          #+#    #+#             */
/*   Updated: 2024/11/20 21:50:29 by albmarqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//-----------//
// LIBRARIES //----------------------------------------------------------------
//-----------//

// Personal
# include "../libft/includes/libft.h"

// External
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

//--------------------//
// DEFINES structures //-------------------------------------------------------
//--------------------//

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
	char		*path;
	int			exit_status;
	int			prev_status;
	t_token		*tokens;
	t_group		*groups;
	t_env		*envp;
}				t_shell;

//-----------------------------------------------------------------------------

void	print_tokens(t_token *tokens); ///////// BORRAR FUNCION
void	print_groups(t_group *group); ///////// BORRAR FUNCION
void	print_array(char **array); ///////// BORRAR FUNCION

//------//
// MAIN //---------------------------------------------------------------------
//------//

// main.c
int		event_hook_readline(void);
t_shell	*init_shell(char **envp);
void	main_loop(t_shell *shell, char *line);
int		main(int argc, char **argv, char **envp);

// tester.c
void	main_tester(char **argv, t_shell *shell);

// utils1.c
int		ft_isspace(char c);
char	*better_strjoin(char const *s1, char const *s2);
char	*split_notspace(t_shell *shell, char *str, char *new, char *aux);
char	*split_isspace(t_shell *shell, char *str, char *new, int *is_var);
char	*space_split(t_shell *shell, char *str, char *new, int *is_var);

// utils_env.c
char	**ft_subs_env(char **array, char *str, int j, int k);
char	**ft_split_env(char *str, char del);
void	fill_envp(t_shell *shell, char **env, t_env *tmp);
char	**get_envp(t_shell *shell);
void	free_envp(char **env, char *cmd);

//--------------//
// 	ENVIRONMENT //-------------------------------------------------------------
//--------------//

// environment.c
void	free_env_value(char **tmp, t_env *new);
void	free_environ(t_shell *shell, t_env *tmp, int i);
t_env	*env_values(char *env);
t_env	*environ(t_shell *shell, char **envp);
char	*search_env(t_shell *shell, char *key);

// env_variable.c
void	set_pwd(t_shell *shell);
void	set_oldpwd(t_shell *shell);
void	set_path(t_shell *shell);
void	set_(t_shell *shell);
void	set_env_var(t_shell *shell);

// env_shlvl.c
void	found_shlvl(t_shell *shell, int i);
void	set_shlvl(t_shell *shell);

//----------//
// BULT-INS //-----------------------------------------------------------------
//----------//

// cd.c
void	args_cd_error(t_shell *shell);
void	file_cd_error(t_shell *shell, char *file, char *oldpwd);
void	update_pwd(t_shell *shell, char *oldpwd);
void	cd(t_shell *shell, char **args);

// echo.c
int		is_n_flag(char *arg);
void	ft_echo(t_shell *shell, char **args);

// env.c
void	env(t_shell *shell);

// exit.c
void	num_exit_error(t_shell *shell, char *arg);
void	args_exit_error(t_shell *shell);
void	exit_shell(t_shell *shell, char **args);

// export_utils.c
void	export_error(t_shell *shell, char *arg);
void	ft_swap(char **a, char **b);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_split_var(t_shell *shell, t_env *new, char *value);

// export_env.c
void	node_dup(t_env **envp, t_env *new, t_env **tmp, t_env **tmp2);
t_env	*envp_dup(t_env *envp);
void	order_dup(t_env *sorted, t_env *first, int len);
void	print_node(t_env *tmp);
int		order_env(t_shell *shell);

// export.c
void	add_one_envp(t_env *tmp, t_env *new);
void	add_envp(t_shell *shell, t_env *new);
int		check_export(char *args);
int		export(t_shell *shell, char **args);

// pwd.c
void	pwd(t_shell *shell);

// unset.c
void	unset_node(t_shell *shell, char *arg);
void	unset(t_shell *shell, char **args);

//---------//
// PARSING //------------------------------------------------------------------
//---------//

// parse.c
int		is_closed_quotes(int type, char *line, int i);
int		double_quotes(t_shell *shell, char *line, int i);
int		tokenize_quotes(t_shell *shell, int type, int j);
int		token_var(t_shell *shell, char *line, int i);
void	parse_line(t_shell *shell);

// token.c
int		token_type(char c);
t_token	*new_token(enum e_token type, char value);
void	add_token(t_shell *shell, t_token *new);
t_token	*create_token(t_shell *shell, enum e_token type, char value);

// group.c
t_token	*group_pipe(t_shell *shell, t_token *tokens);
int		syntax_check_loop(t_shell *shell, t_group *tmp, t_group *next);
void	syntax_check(t_shell *shell);
void	find_cmds(t_shell *shell);
void	group_tokens(t_shell *shell);

// group_utils.c
t_group	*new_group(void);
void	add_group(t_shell *shell, t_group *new);
int		add_args_group(t_shell *shell, char *str, int is_var);

// group_errors.c
void	syntax_error_newline(t_shell *shell);
void	syntax_error(t_shell *shell, char *word);
void	print_ambiguous(t_token *token);
void	ambiguous_error(t_shell *shell, t_group *tmp);

// group_char.c
char	*group_chars_char(t_shell *shell, t_token **tmp, char *str);
char	*group_chars_var_q(t_shell *shell, t_token **tmp, char *str);
char	*group_chars_var(t_shell *shell, t_token **tmp, char *str, int *is_var);
char	*group_chars_empty(t_shell *shell, t_token **tmp, char *str);
t_token	*group_chars(t_shell *shell, t_token *tokens);


// group_redir.c
t_token	*group_in(t_shell *shell, t_token *tokens);
t_token	*group_out(t_shell *shell, t_token *tokens);

// group_var.c
char	*subs_question(t_shell *shell, t_token **tokens, char *old);
void	fill_var_name(t_token **tokens, t_token *tmp, char *str);
char	*get_var_name(t_shell *shell, t_token **tokens, char *old);
char	*search_str_var(t_shell *shell, char *str, char *old);
char	*subs_var(t_shell *shell, t_token **tokens, char *old);

//-----------//
// EXECUTION //----------------------------------------------------------------
//-----------//

// exec_main.c
void	exec_everything(t_shell *shell);

// execution.c
void	exec_cmd(t_shell *shell, t_group *group);
void	exec_block(t_shell *shell, t_group *group);

// exec_commands.c
int		check_script(t_shell *shell, char *cmd, char **env);
int		check_command_file(t_shell *shell, char *cmd, char **env);
char	*check_command(t_shell *shell, char *cmd, char **env);
void	check_cmd(t_shell *shell, t_group *group, char *cmd, char **env); ///// DIVIDIR ESTO

// built-ins.c
int		is_builtin(char *cmd);
void	exec_builtin(t_shell *shell, t_group *group, int i);

// exec_utils.c
int		is_directory(char *path);
int		count_pipes(t_group *groups);
int		check_path(char *path);
void	redirect_pipes(int prev_fd, int next_fd);
void	advance_group(t_group **group);

// get_stuff.c
char	*get_cmd(t_shell *shell, t_group *group);
char	**get_args(t_group *groups);
char	*get_path(t_shell *shell, char **env, char *cmd);

// exec_errors.c
void	no_file_error(t_shell *shell, char *cmd);
void	is_directory_error(t_shell *shell, char *cmd);
void	permission_denied_error(t_shell *shell, char *cmd);
void	command_not_found_error(t_shell *shell, char *cmd);
void	cannot_open_error(t_shell *shell, char *cmd);

// redirections.c
void	input_redirection(t_shell *shell, char *file);
void	output_redirection(t_shell *shell, char *file);
void	append_redirection(t_shell *shell, char *file);
void	heredoc_redirection(t_shell *shell, char *doc);
void	handle_redirections(t_shell *shell, t_group *group);

// heredoc.c
void	heredoc_loop(t_shell *shell, t_group *group, int fd);
void	create_heredoc(t_shell *shell, t_group *group, int hd_num);
void	read_heredocs(t_shell *shell);

// subs_heredoc.c
void	print_prev_status(t_shell *shell, int fd);
void	print_env_var(t_shell *shell, char *line, int *i, int fd);
void	print_var(t_shell *shell, char *line, int *i, int fd);
void	subs_hd(t_shell *shell, char *line, int fd);

// fd_handler.c
int		save_fds(int *stdin, int *stdout);
int		restore_fds(int stdin, int stdout);
int		save_restore_fds(int i);

//---------//
// SIGNALS //------------------------------------------------------------------
//---------//

// signal_init.c
void	init_signal(void);
void	init_signal_hd(void);
void	init_signal_quit(void);

// signal_handler.c
void	signal_handler(int signal);
void	signal_hd(int signal);
void	signal_quit(int signal);

// signal_utils.c
void	disable_echoctl(void);

//------------------//
// ERRORS AND FREES //---------------------------------------------------------
//------------------//

// errors.c
void	malloc_error(void);
void	free_all_malloc(t_shell *shell);
void	hd_error(char *word);
void	perror_error(t_shell *shell, char *word);

// frees.c
void	free_array(char **array);
void	free_heredocs(t_shell *shell);
void	*free_tokens(t_token *token);
void	*free_groups(t_group *group);
void	free_all(t_shell *shell);

#endif
