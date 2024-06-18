/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:55 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/18 11:04:02 by ismirand         ###   ########.fr       */
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
	REDIR_OUT, //>
	D_REDIR_OUT, //>>
	REDIR_IN, //<
	HEREDOC //<<
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

//global variable
extern int	g_exit_status;

//main
int		main(int argc, char **argv, char **envp);

/********************************************************************/
/*     		      AMAURI SPACE	   			 						*/
/********************************************************************/
void	am_function(void);

//parsing_1.c
void	parsing1(char *input, char **envp);

//prompt.c
char	*get_prompt_msg(char **envp);

//frees.c
void	free_dp_char(char **dp_char);
int		free_main_struct(t_mini *mini_d);
int		free_env(t_env *env);
void	clean_tokens(t_mini *mini_d);

//init_values.c
void	init_main_struct(t_mini *mini_d, char **argv, char **envp);

//lexing.c
int		do_lexing(t_mini *mini_d);
void	do_lexing_aux(t_mini *mini_d, int *i, int *state);
int		create_token(t_mini *mini_d, char *input, int state, int len);
int		define_state(char ch, int state, int *i);
int		specch(char ch);

//token.c
t_token	*init_token(char *content, int type, int id);int prepare_parsing(t_mini	*mini_d)
{
		
}
t_token	*set_token_head(t_mini *mini_d);
t_token *set_token_tail(t_mini *mini_d);
int		token_lstadd_back(t_mini *mini_d, t_token *new_token);
int		alloc_tokenstruct(t_mini *mini_d);

//support.c
void	print_nodes(t_mini *mini_d);
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

//parsing/prepare.c


/********************************************************************/
/*     		       ISA SPACE	   									*/
/********************************************************************/
//env/env.c
int		get_env(char **env, t_env *env_var);

//isa_test.c
void	isa_function2(void);

//build_in/*.c
int		buildin_pwd(void);
void	buildin_env(t_env *env_var);
//echo
//cd
//env
//exit
//export
//unset


#endif