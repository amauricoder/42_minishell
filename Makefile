# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aconceic <aconceic@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/17 16:41:12 by aconceic          #+#    #+#              #
#    Updated: 2024/06/08 16:03:00 by aconceic         ###   ########.fr        #
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
RESET = \e[0m

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

ISA_SRC = isa_test.c build_in/buildin_echo.c build_in/buildin_pwd.c env/env.c \
		  build_in/buildin_env.c init_values.c \

AM_SRC = am_test.c parsing_1.c prompt.c frees.c lexing/lexing_1.c lexing/lexing_2.c\
		lexing/lexing_3.c support.c\

##############################################
#                COMPILATION                 #
##############################################
CC = cc
GCC = cc -g
CFLAGS = -Wall -Wextra -Werror

##############################################
#                   RULES                    #
##############################################
all : $(NAME)

$(OBJ_DIR) :
	@echo "$(ORANGE)[!]$(RESET) Creating directory for objects ..."
	mkdir $@

$(NAME) : $(OBJ) $(LIBFT_LIB)
	@echo "$(ORANGE)[!]$(RESET) Working on project ... "
	$(GCC) $(CFLAGS) $(OBJ) -lreadline $(SRC_DIR)main.c $(LIBFT_LIB) $(GNL_LIB) -o $(NAME)
	@echo "$(GREEN)[✔]$(RESET) $(BLUE)Ok!$(RESET) "

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_DIR) $(OBJ_DIR)build_in $(OBJ_DIR)env $(OBJ_DIR)lexing
	@echo "$(ORANGE)[!]$(RESET) Creating objects ..."
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)[✔]$(RESET) $(BLUE)Objects Ok!$(RESET) "

$(OBJ_DIR)build_in:
	@echo "$(ORANGE)[!]$(RESET) Creating directory for build_in objects ..."
	mkdir -p $(OBJ_DIR)build_in

$(OBJ_DIR)env:
	@echo "$(ORANGE)[!]$(RESET) Creating directory for env objects ..."
	mkdir -p $(OBJ_DIR)env

$(OBJ_DIR)lexing:
	@echo "$(ORANGE)[!]$(RESET) Creating directory for lexing objects ..."
	mkdir -p $(OBJ_DIR)lexing

$(LIBFT_LIB) : $(LIBFT_DIR)
	@echo "$(ORANGE)[!]$(RESET) Working on LIBFT_LIB ..."
	$(MAKEC) $(LIBFT_DIR) bonus
	$(MAKEC) $(PRINTF_DIR)
	$(MAKEC) $(GNL_DIR)
	@echo "$(GREEN)[✔]$(RESET) $(BLUE)LIBFT Ok!$(RESET)"

clean :
	@echo "$(ORANGE)[!]$(RESET) Executing cleaning ..."
	$(RM) $(OBJ_DIR)
	$(RM) $(BONUS_OBJ_DIR)
	$(MAKECLEANC) $(LIBFT_DIR)
	@echo "$(GREEN)[✔]$(RESET) $(BLUE)Cleaning Ok!$(RESET) "

fclean :
	@echo "$(ORANGE)[!]$(RESET) Executing full cleaning..."
	$(RM) $(NAME) $(OBJ_DIR)
	$(RM) $(BONUS_NAME) $(BONUS_OBJ_DIR)
	$(RM) library/minilibx-linux
	make fclean -C $(LIBFT_DIR)
	@echo "$(GREEN)[✔]$(RESET) $(BLUE)full cleaning!$(RESET) "

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