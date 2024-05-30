/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:55 by aconceic          #+#    #+#             */
/*   Updated: 2024/05/30 18:31:45 by aconceic         ###   ########.fr       */
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
	WHITE_SPACE
}	e_token;

//tokens
typedef struct s_token
{
	int				len;
	char			*content;
	enum e_token	type;
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

//init_values.c
void	init_main_struct(t_mini *mini_d, char **argv, char **envp);

//lexing1.c
int		do_lexing(t_mini *mini_d);
int		alloc_tokenstruct(t_mini *mini_d);
int		is_quote(char ch);
int		is_space(char ch);
int		init_token(t_mini *mini_d, char *content, e_token type);
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