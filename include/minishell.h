/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:14:55 by aconceic          #+#    #+#             */
/*   Updated: 2024/05/18 14:46:12 by aconceic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/*************************/
/*     External Libs     */
/*************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h> //perror
#include <dirent.h> //opendir
#include <sys/types.h> //fork()
#include <sys/wait.h> //wait()
#include <sys/resource.h> //wait3, wait4
#include <sys/stat.h> //stat
#include <sys/ioctl.h> //ioctl

/*************************/
/*     	 LIBFT/GNL 		 */
/*************************/
#include "../libraries/libft/libft.h"

/*************************/
/*     		COLORS	     */
/*************************/
# define RESET   "\033[0m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MGT "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"

//main
int     main(int argc, char **argv);

/*********************************************/
/*     		      AMAURI SPACE	   			 */
/*********************************************/
void    am_function(void);

/*********************************************/
/*     		       ISA SPACE	   			 */
/*********************************************/
void    isa_function(void);

#endif