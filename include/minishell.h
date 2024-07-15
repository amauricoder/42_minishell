/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:55 by aconceic          #+#    #+#             */
/*   Updated: 2024/07/15 18:40:04 by aconceic         ###   ########.fr       */
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
#include <stdbool.h>

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
}	e_token;

typedef enum e_tstate
{
	GENERAL,
	IN_QUOTE,
	IN_DQUOTE
}	e_tstate;

//tokens
typedef struct s_token
{
	int				id;
	int				len;
	char			*content;
	int				type;
	enum e_token	state;
	struct s_token	*head;
	struct s_token	*tail;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

//env
typedef struct s_env
{
	int				env_id;
	char			*env_name;
	struct s_env	*next;
}	t_env;

//main struct
typedef struct s_mini
{
	char	*input;
	char	*prompt;
	char	**argv_cp;
	int		token_type;
	t_env	*env_d;
	t_token	*token;
}				t_mini;

//main parsing struct

typedef struct s_exec
{
	int		type;
	int		id;
	char	**args; //cmds and arguments of the commands
}	t_exec;

typedef struct s_pipe
{
	int		type;
	int id;
	//pointer to the left -> this node can point for a redir or exec
	void 	*left;
	//pointer to the right
	void 	*right;
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
void	free_dp_char(char **dp_char);
int		free_main_struct(t_mini *mini_d);
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
t_token *set_token_tail(t_mini *mini_d);
int		token_lstadd_back(t_mini *mini_d, t_token *new_token);
//int		alloc_tokenstruct(t_mini *mini_d);

//support.c
void	print_nodes(t_mini *mini_d);
void	printf_matriz(char **to_print);
char	*ft_strdup_qt(char *str, int qt);
int		error_msg_and_exit(char *str, int exit_value);

//check_input.c
int		is_argument_valid(int argc, char **env);
int		check_input(char *input);
int		is_quotes_closed(char *input);
int		is_pipe_the_last(char *input);

//signals.c
void	signals_init(void);
void	signal_handler(int sig);
void	signals_child(void);
void	signal_handler_child(int sig);

//expand/expansion.c
int		find_expansion(t_mini	*mini_d);
char	*env_expanded(char *content);
void	expand_dollar(t_token *token, int i);
char	*change_content(t_token *token, int i);
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
int		build_tree(t_mini *mini_d);
void	*parse_exec(t_mini *mini_d);
void	*parse_redir(t_mini *mini_d, void *root);
int		have_command(t_mini *mini_d);
char	**get_cmd(t_mini *mini_d);
char	*get_redir_name(t_token *node);
t_token *get_last_redir(t_token *node, int first_interaction);
t_redir	*create_redir_node(void *down, int id, t_token *node);
void	print_tree(void *root);

//build_in/echo.c
void	execute_buildins(t_mini *mini_d);
void	echo(t_mini *mini_d);

//env/env.c
int		get_env(char **env, t_env *env_var);

//build_in/*.c
int		buildin_pwd(void);
void	buildin_env(t_env *env_var);

#endif