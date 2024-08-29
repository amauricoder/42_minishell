/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:55 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/29 17:45:53 by ismirand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*************************/
/*     External Libs     */
/*************************/
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h> //perror
# include <dirent.h> //opendir
# include <sys/types.h> //fork()
# include <sys/wait.h> //wait()
# include <sys/resource.h> //wait3, wait4
# include <sys/stat.h> //stat
# include <sys/ioctl.h> //ioctl
# include <readline/readline.h>//readline
# include <readline/history.h>//add_history
# include <stdbool.h>
# include <fcntl.h> //open() flags
# include <unistd.h> 
# include <sys/types.h>
# include <sys/stat.h>
# include <locale.h>

/*************************/
/*     	 LIBFT/GNL 		 */
/*************************/
# include "../libraries/libft/libft.h"

/*************************/
/*     		COLORS	     */
/*************************/
# define RESET	"\033[0m"
# define RED	"\033[31;1m"
# define GREEN	"\033[32;1m"
# define YELLOW	"\033[33;1m"
# define BLUE	"\033[34;1m"
# define MGT	"\033[35;1m"
# define CYAN	"\033[36;1m"
# define WHITE	"\033[37;1m"
# define ORANGE "\033[1;38;5;208m"

/***********************************/
/* ERROR MSG && EXIT_STATUS VALUES */
/***********************************/
# define INT_MIN -2147483648
# define INT_MAX 2147483647
# define SYNTAX_ERR "syntax error"
# define PWD_ERR "pwd: -*: invalid option\npwd: usage: pwd"
# define PWD_ERR_DIR "pwd: cannot access '': No such file or directory"
# define CD_ERR_ARG "cd: too many arguments"
# define CD_ERR_DIR "cd: no such file or directory"
# define EXIT_ERR_ARG "exit: too many arguments"
# define EXIT_ERR_NUM "exit: numeric argument required"
# define FORK_ERR "fork: error during fork"
# define NO_CMD " : command not found"
# define NO_DIR " : no such file or directory"
# define H_NOT "minishell: cd: HOME not set"
# define OLDPWD_NOT "minishell: cd: OLDPWD not set"

# define EXP "minishell: export: "
# define N_VAL ": not a valid identifier"

# define D_ENV "minishell: env: "
# define D_CD "minishell: cd: "
# define NO_FILE ": No such file or directory"
# define TOO_ARGS "too many arguments"

# define ENV_ERR "minishell: env: No such file or directory"

/*************************/
/*    structs and enun	 */
/*************************/
typedef enum e_token
{
	WORD,
	W_SPACE,
	D_QUOTE,
	S_QUOTE,
	PIPE,
	ENV,
	R_OUT, //>
	D_R_OUT, //>>
	R_IN, //<
	HEREDOC, //<<
	FILE_NAME
}	t_token_type;

typedef enum e_tstate
{
	GENERAL,
	IN_QUOTE,
	IN_DQUOTE
}	t_tstate;

typedef enum e_builtins
{
	NO_B,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	B_ENV,
	EXIT
}	t_builtins;

//tokens
typedef struct s_token
{
	int				id;
	int				len;
	char			*content;
	int				type;
	int				builtin;
	enum e_token	state;
	struct s_token	*head;
	struct s_token	*tail;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//env
typedef struct s_env
{
	int				id;
	char			*name;
	struct s_env	*next;
}	t_env;

//export 
typedef struct s_export
{
	int				exp_id;
	char			*exp_name;
	struct s_export	*next;
}	t_export;

//main struct
typedef struct s_mini
{
	char	*input;
	char	*prompt;
	char	**argv_cp;
	int		token_type;
	void	*root;
	int		exit_status;
	int		exst_printable;
	int		stdfds[2];
	int		qt_heredocs;
	t_env	*env_d;
	t_env	*export;
	t_token	*token;
}				t_mini;

//main parsing struct
typedef struct s_exec
{
	int		type;
	int		id;
	int		builtin;
	char	**args;
}	t_exec;

typedef struct s_pipe
{
	int		type;
	int		id;
	void	*left;
	void	*right;
}	t_pipe;

typedef struct s_redir
{
	int		type;
	int		id;
	char	*fname;
	int		len;
	void	*down;
	char	*hd_tmp;
}	t_redir;

//global variable
extern int	g_exit_status;

//main
int		main(int argc, char **argv, char **envp);

//main_support.c
void	run_minishell(t_mini *mini_d);
void	prompt_and_input(t_mini *mini);
void	update_exit_status(t_mini *mini_d);
//debug.c
void	debug_nodes_and_tree(t_mini *mini_d);

//prompt.c
char	*get_prompt_msg(char **envp);

//frees.c
void	free_and_exit(t_mini *mini, int exit_nbr);
int		free_main_struct(t_mini *mini_d);
void	free_matriz(char **dp_char);
int		free_env(t_env *env);
void	free_tokens(t_mini *mini_d);
//frees2.c
int		free_in_execution(t_mini *mini_d, int exit_status);

//init_values.c
void	init_main_struct(t_mini *mini_d, char **argv, char **envp);

//lexing.c
int		do_lexing(t_mini *mini_d);
void	do_lexing_aux(t_mini *mini_d, int *i, int *state);
void	in_quote(t_mini *mini_d, int *i, int *state, char flag);
void	in_special(t_mini *mini_d, int *i, int *state, int type);
void	redir_env(t_mini *mini_d, int *i, int *state, int type);

//lexing_support.c
void	define_type_env(t_mini *mini_d);
int		create_token(t_mini *mini_d, char *input, int state, int len);
int		specch(char ch);

//token.c
t_token	*init_token(char *content, int type, int id);
t_token	*set_token_head(t_mini *mini_d);
t_token	*set_token_tail(t_mini *mini_d);
int		token_lstadd_back(t_mini *mini_d, t_token *new_token);

//support.c
void	print_nodes(t_mini *mini_d);
void	printf_matriz(char **to_print);
char	*ft_strdup_qt(char *str, int qt);
int		err_msg(t_mini *d, char *str, int ev, int fr);
char	*join_three(char *s1, char *s2, char *s3, int flag);

//check_input.c
int		is_argument_valid(int argc, char **env);
int		is_input_invalid(t_mini *mini, char *input);
int		is_quotes_closed(char *input);

//check_input2.c
int		is_pipe_last_or_first(char *input);
int		is_redir_invalid(char *input);
int		is_next_word_invalid(char *input);

//signals.c
void	signals_init(void);
void	signal_handler(int sig);
void	default_sig(void);
void	update_signals(void);

//expand/expansion.c
int		find_expansion(t_mini	*mini_d);
char	*env_expanded(t_mini *mini_d, char *content);
void	expand_dollar(t_mini *mini_d, t_token *token, int i);
char	*change_content(t_mini *mini_d, t_token *token, int i);
void	clean_token(t_mini *mini_d);
void	update_word_to_file(t_mini *mini_d);

//expand/expansion_support.c
void	assemble_word_tokens(t_mini *mini_d);
int		check_dollar(char *nd_content);
int		have_spacial_char(char *word);
int		aftdol_len(char *content);
int		ft_strlen_char(char *str, char ch);
//char	*aftdol_position(char *big, char *little);

//parsing/parsing.c
void	*do_parsing(t_mini *mini_d, t_token *token);
void	*parse_exec(t_token *token);
void	*parse_redir(t_token *token, void *root);
void	*parse_pipe(void *left, void *right);

//parsing/tree_support.c
t_token	*have_command(t_token *node);
t_redir	*create_redir_node(void *down, int *id, t_token *node);
char	*get_redir_name(t_token *node);
int		get_qt_cmd_tokens(t_token *token);
void	free_tree(void *root);

//parsing/tree_support2.c
t_token	*get_last_or_pipe(t_token *to_advance);
char	**get_cmd(t_token *token);
t_token	*get_last_redir(t_token *node, int first_interaction);
t_token	*get_last_redir_aux(t_token *last);

//parsing/tree_debug.c
void	print_tree(void *node, const char *prefix, bool isLeft);
void	print_exec(void *node, const char *prefix, bool isLeft);
void	print_redir(void *node, const char *prefix, bool isLeft);
void	print_pipe(void *node, const char *prefix, bool isLeft);

//parsing/tree_free.c
void	free_exec(void *root);
void	free_redir(void *root);
void	free_tree(void *root);
void	free_pipe(void *root);

//exec/execution.c
int		do_execution(t_mini *mini_d, void *root);
int		handle_exec_cmd(t_mini *mini_d, void *root);
void	set_child_exit(int wstatus, t_mini *mini);

//exec/exec_redir.c
void	handle_redir_nodes(t_mini *mini_d, void *root);
void	exec_redir_in(t_mini *mini_d, t_redir *node);
void	exec_redir_out(t_mini *mini_d, t_redir *node);

//exec/exec_cmd.c
int		execute_cmd(t_mini *mini, void *root);
char	**find_path_env(t_mini	*mini_d);
char	**get_env_matriz(t_mini *mini_d);
char	*create_cmdpath(char *possible_path, char *command);
int		execute_buildins(t_mini *mini, void *root);

//exec/exec_cmd2.c
int		treat_exec_exception(void *root);
void	treat_exec_exception_aux(t_exec *exec_nd, int *j);

//exec/exec_pipe.c
int		handle_pipe(t_mini *mini_d, void *root);
int		exec_pipe(t_mini *mini_d, void *root, int p_fd[2], int is_left);

//exec/exec_heredoc.c
int		redirect_heredoc(t_mini *mini_t, t_redir *node);
char	*get_heredoc_name(t_mini *mini, int id, int invert);
void	open_heredocs(t_mini *mini, void *root);

//exec/exec_heredoc2.c
int		handle_heredoc(t_mini *mini_d, t_redir *hd_node);
int		do_expansion(char *input);
char	*hd_expand_heredoc(t_mini *mini_d, char *line);
char	*hd_change_content(t_mini *mini_d, char *line, int i);
int		write_on_heredoc(t_mini *d, int fd, t_redir *nd);

//builtins/support.c
void	define_builtins(t_mini *mini_d);
void	tests_builtins(t_mini *mini, void *root);

//builtins/echo.c
int		echo(char **str);
int		is_echoflag(char *str, int *new_line);

//builtins/pwd.c
int		pwd(t_mini *mini, char **str);

//builtins/bt_env.c
int		env(t_mini *mini, t_env *env_var, char **str);
char	*env_join(char *old, char *to_add, t_env *env);

//builtins/cd.c
int		cd(t_mini *mini, char **str);
int		cd_home(t_mini *mini, char **str);
int		cd_oldpwd(t_mini *mini, char **str);
int		safe_chdir(t_mini *mini, char *dir);
char	*find_last_dir(char *dir);
char	*get_path(t_mini *mini, char *str);
int		back_cd(t_mini *mini_d, char **str);
int		update_pwd_oldpwd(t_mini *mini, char *last_dir);

//builtins/exit.c
void	exit_read(t_mini *mini_d, char **str);
int		exit_number(t_mini *mini, char **str);
int		str_digit(char *str);

//builtins/export.c
int		export(t_mini *mini, char **str);
void	read_arg(char *str, char **tmp, t_env *exp);
void	export_add(t_mini *mini, char *str, char *name);
int		export_add_support(t_mini *mini, char *str, char *name, t_env *env);

//builtins/export_create.c
char	*exp_join(char *old, char *to_add, t_env *env);
int		export_create(t_mini *mini);
char	*env_to_export(t_env *env);
t_env	*lst_sort(t_env *env);
int		print_export(t_mini *mini);

//builtin/unset.c
int		unset(t_mini *mini, char **args);
void	unset_env(t_mini *mini, char *name);
void	unset_export(t_mini *mini, char *name);

//env/env.c
int		copy_env(char **env, t_env **env_var);
int		ft_getenv(t_mini *mini_d, char *to_find);
t_env	*env_add(char *str);
char	*expand(t_mini *mini_d, char *to_find);
int		replace_env_value(t_mini *mini, char *env_name, char *new);

#endif