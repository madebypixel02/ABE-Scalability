# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aperez-b <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/17 09:03:14 by aperez-b          #+#    #+#              #
#    Updated: 2022/04/25 12:05:01 by aperez-b         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Color Aliases
DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

SHELL=/bin/bash

# Make variables
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
CC = gcc
AR = ar rcs
SRC_DIR = src
INC_DIR = inc
SRCB_DIR = srcb
OBJ_DIR = obj
OBJB_DIR = objb
BIN_DIR = bin
BIN = cp_abe
NAME = $(BIN_DIR)/$(BIN)
PRINTF = LC_NUMERIC="en_US.UTF-8" printf

SRC = main.c utils.c ft_strdup.c	\
	ft_substr.c ft_strlcpy.c		\
	ft_atoi.c ft_itoa.c ft_nbrlen.c	\
	ft_putstr_fd.c ft_isspace.c		\
	ft_strjoin.c ft_putnbr_fd.c		\
	ft_putchar_fd.c ft_strlen.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Progress vars
SRC_COUNT_TOT := $(shell expr $(shell echo -n $(SRC) | wc -w) - $(shell ls -l $(OBJ_DIR) 2>&1 | grep ".o" | wc -l) + 1)
ifeq ($(shell test $(SRC_COUNT_TOT) -le 0; echo $$?),0)
	SRC_COUNT_TOT := $(shell echo -n $(SRC) | wc -w)
endif
SRC_COUNT := 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))

all: $(NAME)

$(NAME): create_dirs $(OBJ)
	@$(CC) $(CFLAGS) $(CDEBUG) $(OBJ) -o $@
	@$(PRINTF) "\r%100s\r$(GREEN)$(BIN) is up to date!$(DEFAULT)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $(BLUE)$<$(DEFAULT)..." "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
	@$(CC) $(CFLAGS) -c $< -o $@

create_dirs:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

clean:
	@$(PRINTF) "$(CYAN)Cleaning up object files in cp_abe...$(DEFAULT)\n"
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) -r $(BIN_DIR)
	@$(PRINTF) "$(CYAN)Removed $(NAME)$(DEFAULT)\n"

norminette:
	@$(PRINTF) "$(CYAN)\nChecking norm for cp_abe...$(DEFAULT)\n"
	@norminette -R CheckForbiddenSourceHeader $(SRC_DIR) $(INC_DIR)

git:
	git add .
	git commit
	git push

re: fclean
	@make all

.PHONY: all clean fclean bonus re norminette create_dirs git
