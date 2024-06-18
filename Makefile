# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ismirand <ismirand@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 16:41:12 by aconceic          #+#    #+#              #
#    Updated: 2024/06/18 10:40:06 by ismirand         ###   ########.fr        #
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
OBJ = $(addprefix $(OBJ_DIR), $(ISA_SRC:.c=.o)) $(addprefix $(OBJ_DIR), $(AM_SRC:.c=.o))
SRC_DIR = ./source/

ISA_SRC = build_in/buildin_echo.c build_in/buildin_pwd.c env/env.c\
		  build_in/buildin_env.c init_values.c\

AM_SRC = parsing_1.c prompt.c frees.c lexing/lexing.c lexing/token.c\
		support.c check_input.c signals.c parsing/prepare.c\

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

$(OBJ_DIR) :
	@echo "$(CYAN)[!]$(RESET) Creating directory for objects ..."
	mkdir $@

$(NAME) : $(OBJ) $(LIBFT_LIB)
	@echo "$(CYAN)[!]$(RESET) Working on project ... "
	$(GCC) $(CFLAGS) $(OBJ) -lreadline $(SRC_DIR)main.c $(LIBFT_LIB) $(GNL_LIB) -o $(NAME) $(LDFLAGS)
	@echo "$(GREEN)[✔] Ok!$(RESET) "

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR) $(OBJ_DIR)build_in $(OBJ_DIR)env $(OBJ_DIR)lexing $(OBJ_DIR)parsing
	@echo "$(CYAN)[!]$(RESET) Creating object $@ ..."
	$(GCC) $(CFLAGS) -c $< -o $@
#@echo "$(GREEN)[✔]$(RESET) $(BLUE)Object $@ Ok!$(RESET) "

$(OBJ_DIR)build_in:
	@echo "$(CYAN)[!]$(RESET) Creating directory for build_in objects ..."
	mkdir -p $(OBJ_DIR)build_in

$(OBJ_DIR)env:
	@echo "$(CYAN)[!]$(RESET) Creating directory for env objects ..."
	mkdir -p $(OBJ_DIR)env

$(OBJ_DIR)lexing:
	@echo "$(CYAN)[!]$(RESET) Creating directory for lexing objects ..."
	mkdir -p $(OBJ_DIR)lexing

$(OBJ_DIR)parsing:
	@echo "$(CYAN)[!]$(RESET) Creating directory for parsing objects ..."
	mkdir -p $(OBJ_DIR)parsing

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
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#              NOTES AND REMINDERS           #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#
#        $< represent the prerequisite       #
#        $@ represent the target             #
#~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#