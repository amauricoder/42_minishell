/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:55 by aconceic          #+#    #+#             */
/*   Updated: 2024/08/14 17:27:59 by ismirand         ###   ########.fr       */
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
# define SYNTAX_ERR "minishell : syntax error"
# define PWD_ERR "minishell : pwd: -*: invalid option\npwd: usage: pwd"
# define PWD_ERR_DIR "minishell : pwd: cannot access '': No such file or directory"
# define CD_ERR_ARG "minishell : cd: too many arguments"
# define CD_ERR_DIR "minishell : cd: no such file or directory"
# define EXIT_ERR_ARG "minishell : exit: too many arguments"
# define EXIT_ERR_NUM "minishell : exit: numeric argument required"

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
	char	**args; //cmds and arguments of the commands
}	t_exec;

typedef struct s_pipe
{
	int		type;
	int		id;
	void	*left; //pointer to the left -> this node can point for a redir or exec 
	void	*right; //pointer to the right
}	t_pipe;

typedef struct s_redir
{
	int		type;
	int		id;
	//copy content
	char	*fname;
	int		len;
	//Pointer -> This pointer can point to a redir or exec
	void	*down;
}	t_redir;

//global variable
extern int	g_exit_status;

//main
int		main(int argc, char **argv, char **envp);

//prompt.c
char	*get_prompt_msg(char **envp);

//frees.c
void	free_and_exit(t_mini *mini);
int		free_main_struct(t_mini *mini_d);
void	free_matriz(char **dp_char);
int		free_env(t_env *env);
void	free_tokens(t_mini *mini_d);

//init_values.c
void	init_main_struct(t_mini *mini_d, char **argv, char **envp);

//lexing.c
int		do_lexing(t_mini *mini_d);
void	do_lexing_aux(t_mini *mini_d, int *i, int *state);
void	in_quote(t_mini *mini_d, int *i, int *state, char flag);
void	in_special(t_mini *mini_d, int *i, int *state, int type);
void	redir_env(t_mini *mini_d, int *i, int *state, int type);

//lexing_support.c
void	find_env(t_mini *mini_d);
int		create_token(t_mini *mini_d, char *input, int state, int len);
int		specch(char ch);

//token.c
t_token	*init_token(char *content, int type, int id);
t_token	*set_token_head(t_mini *mini_d);
t_token	*set_token_tail(t_mini *mini_d);
int		token_lstadd_back(t_mini *mini_d, t_token *new_token);
//int		alloc_tokenstruct(t_mini *mini_d);

//support.c
void	print_nodes(t_mini *mini_d);
void	printf_matriz(char **to_print);
char	*ft_strdup_qt(char *str, int qt);
int		error_msg(t_mini *mini, char *str, int exit_value);

//check_input.c
int		is_argument_valid(int argc, char **env);
int		check_input(t_mini *mini, char *input);
int		is_quotes_closed(char *input);
int		is_pipe_last_or_first(char *input);
int		is_redir_invalid(char *input);
int		is_next_word_invalid(char *input);

//signals.c
void	signals_init(void);
void	signal_handler(int sig);
void	signals_child(void);
void	signal_handler_child(int sig);

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
void	*build_tree(t_token *token);
void	*parse_exec(t_token *token);
void	*parse_redir(t_token *token, void *root);
void	*parse_pipe(void *left, void *right);

//parsing/tree_support.c
int		have_command(t_token *node);
t_redir	*create_redir_node(void *down, int id, t_token *node);
char	*get_redir_name(t_token *node);
int		get_qt_cmd_tokens(t_token *token);
void	free_tree(void *root);

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

//parsing/tree_support2.c
t_token	*get_last_or_pipe(t_token *to_advance);
char	**get_cmd(t_token *token);
t_token	*get_last_redir(t_token *node, int first_interaction);

//exec/exec.c
void	exec_through_tree(t_mini *mini_d, void *root);
void	exec_tree(t_mini *mini_d, void *root, int is_child);

//exec/exec_redir.c
void	handle_redir_nodes(t_mini *mini_d, void *root);
void	exec_redir_in(t_mini *mini_d, t_redir *node);
void	exec_redir_out(t_mini *mini_d, t_redir *node);

//exec/exec_cmd.c
int		execute_cmd(t_mini *mini, void *root);
char	**find_path_env(t_mini	*mini_d);
char	**get_env_matriz(t_mini *mini_d);
char	*create_cmdpath(char *possible_path, char *command);
void	execute_buildins(t_mini *mini, void *root);

//builtins/support.c
void	define_builtins(t_mini *mini_d);
void	tests_builtins(t_mini *mini, void *root);

//builtins/echo.c
void	echo(char **str);
int		is_echoflag(char *str, int *new_line);

//builtins/pwd.c
int		pwd(t_mini *mini, char **str);

//builtins/bt_env.c
void	env(t_env *env_var);

//builtins/cd.c
int		cd(t_mini *mini, char **str);
int		safe_chdir(t_mini *mini, char *dir);
char	*find_last_dir(char *dir);
char	*get_path(t_mini *mini, char *str);

//builtins/exit.c
void	exit_read(t_mini *mini_d, char **str);
int		exit_number(t_mini *mini, char **str);
int		str_digit(char *str);

//builtins/export.c
t_env	*export_create(t_mini *mini);
void	env_export(t_env *env, t_env **export);
int		export_read(t_mini *mini, char **str);

//env/env.c
int		copy_env(char **env, t_env **env_var);
int		ft_getenv(t_mini *mini_d, char *to_find);

#endif