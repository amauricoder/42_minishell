# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 16:41:12 by aconceic          #+#    #+#              #
#    Updated: 2024/07/20 12:44:11 by aconceic         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##############################################
#                  COLORS                    #
##############################################
GREEN = \e[0;32m
BLUE = \e[1;034m
RED = \e[0;31m
MAGENTA = \033[1;35m
ORANGE = \033[1;38;5;208m
GREY = \033[0;37m
CYAN = \e[1;36m
RESET = \e[0m
CYAN = \e[0;36m

##############################################
#                  COMMANDS                  #
##############################################
MAKEC = make -C
MAKECLEANC = make clean -C
RM = rm -rf

##############################################
#                 MAIN SOURCES               #
##############################################
#Libraryes
LIBFT_DIR = libraries/libft/
LIBFT_LIB = $(LIBFT_DIR)libft.a
PRINTF_DIR = $(LIBFT_DIR)/ft_printf
GNL_DIR = $(LIBFT_DIR)get_next_line/
GNL_LIB = $(GNL_DIR)gnl.a

#Project
NAME = minishell
OBJ_DIR = ./objs/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))
SRC_DIR = ./source/

SRC = prompt.c frees.c lexing/lexing.c lexing/lexing_support.c\
		lexing/token.c support.c check_input.c signals.c expand/expansion.c\
		expand/expansion_support.c parsing/parsing.c parsing/tree_debug.c\
		parsing/tree_support.c parsing/tree_free.c parsing/tree_support2.c\
		env/env.c init_values.c builtins/echo.c builtins/pwd.c\
		builtins/support.c builtins/cd.c\

##############################################
#                COMPILATION                 #
##############################################
CC = cc
LDFLAGS = -lreadline
GCC = cc -g
CFLAGS = -Wall -Wextra -Werror

##############################################
#                   RULES                    #
##############################################
all : $(NAME)

$(NAME) : $(OBJ) $(LIBFT_LIB)
	@echo "$(CYAN)[!]$(RESET) Working on project ... "
	$(GCC) $(CFLAGS) $(OBJ) -lreadline $(SRC_DIR)main.c $(LIBFT_LIB) $(GNL_LIB) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)[✔] Ok!$(RESET) "

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@echo "$(CYAN)[!]$(RESET) Creating object $@ ..."
	mkdir -p $(dir $@)
	$(GCC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB) : $(LIBFT_DIR)
	@echo "$(CYAN)[!]$(RESET) Working on LIBFT_LIB ..."
	$(MAKEC) $(LIBFT_DIR) bonus > /dev/null 2>&1
	$(MAKEC) $(PRINTF_DIR) > /dev/null 2>&1
	$(MAKEC) $(GNL_DIR) > /dev/null 2>&1
	@echo "$(GREEN)[✔] LIBFT Ok!$(RESET)"

clean :
	@echo "$(CYAN)[!]$(RESET) Executing cleaning ..."
	$(RM) $(OBJ_DIR)
	$(RM) $(BONUS_OBJ_DIR)
	$(MAKECLEANC) $(LIBFT_DIR) 
	@echo "$(GREEN)[✔]$(RESET) $(BLUE)Cleaning Ok!$(RESET) "

fclean :
	@echo "$(RED)[!] Executing full cleaning..."
	$(RM) $(NAME) $(OBJ_DIR)
	$(RM) $(BONUS_NAME) $(BONUS_OBJ_DIR)
	$(RM) library/minilibx-linux
	make fclean -C $(LIBFT_DIR) > /dev/null 2>&1
	@echo "$(GREEN)[✔]$(RESET) $(BLUE)Full cleaning!$(RESET) "

re : fclean all
	@echo "$(GREEN)[✔]$(RESET) $(MAGENTA)Refresh Ok!$(RESET) "

.SILENT:
.PHONY: all clean fclean re
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#                NOTES AND REMINDERS            #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#          $< represent the prerequisite        #
#          $@ represent the target              #
# mkdir -p make parent directory without errors #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#