# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lsordo <lsordo@student.42heilbronn.de>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/11 09:33:51 by lsordo            #+#    #+#              #
#    Updated: 2023/04/19 16:23:14 by lsordo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME = $(shell uname)
CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -MMD

#COLORS-----------------------------------------------------------------------#
BRED	=	\033[1;31m
BGREEN	=	\033[1;32m
BYELLOW	=	\033[1;33m
BLUE	=	\033[1;34m
WHITE	=	\033[0m
#-----------------------------------------------------------------------------#

COLOR_MAKE = $(BGREEN)
COLOR_INSTALL = $(BYELLOW)
COLOR_CLEAN = $(BRED)

NAME = philo

SRC_DIR =	./src/
OBJ_DIR =	./obj/
INC_DIR =	-I ./inc

SRC =		philo.c \
			utils_check.c \
			utils_errormgt.c \
			utils_generic.c \
			utils_init.c \
			utils_life.c \
			utils_thread.c

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
DEP = $(SRC:%.c=$(OBJ_DIR)%.d)

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@echo "$(COLOR_MAKE)Make philo...$(DEFCL)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

-include $(DEP)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) $(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p ./obj

clean:
	@echo "$(BRED)Clean objects...$(DEFCL)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(BRED)Clean exec...$(DEFCL)"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
