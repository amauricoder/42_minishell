/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:55 by aconceic          #+#    #+#             */
/*   Updated: 2024/06/08 16:14:58 by aconceic         ###   ########.fr       */
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
# include <readline/readline.h>
# include <readline/history.h>
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
# define GREEN	"\033[32m"
# define YELLOW	"\033[33m"
# define BLUE	"\033[34m"
# define MGT	"\033[35m"
# define CYAN	"\033[36m"
# define WHITE	"\033[37m"

/*************************/
/*    structs and enun	 */
/*************************/
typedef enum e_token
{
	WHITE_SPACE,
	WORD,
	DQUOTE
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
	enum e_token	type;
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
	t_env	*env_d;
	t_token	*token;
}				t_mini;

/*********************************************/
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

//lexing_1.c
int		do_lexing(t_mini *mini_d);
int		create_token(t_mini *mini_d, char *input, int state, int len);
int		define_state(char ch, int state, int *i);
int		get_token_type(char *input);

//lexing_2.c
t_token	*init_token(char *content, e_token typem, int id);
t_token	*set_token_head(t_mini *mini_d);
t_token *set_token_tail(t_mini *mini_d);
int		token_lstadd_back(t_mini *mini_d, t_token *new_token);
int		alloc_tokenstruct(t_mini *mini_d);

//lexing_3.c
int		is_quote(char ch);
int		is_space(char ch);
int		is_dquote(char ch);
int		is_special_char(char ch);

//support.c
void	print_nodes(t_mini *mini_d);
char	*ft_strdup_qt(char *str, int qt);

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