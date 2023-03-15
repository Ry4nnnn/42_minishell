# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 21:58:29 by welim             #+#    #+#              #
#    Updated: 2023/03/14 14:23:30 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

LIB			:= -Llibft -lft

INCLUDE		:= -I./includes -Ilibft/srcs -I./readline-8.1/include

CFLAGS		:= $(INCLUDE) -fcommon #-Wall -Wextra -Werror #-fsanitize=address

ifeq ($(DB), 1)
	CFLAGS	+= -fsanitize=address -g3
endif

CC			:= gcc

NEWLINE 	= \e[1K\r

READLINE	:= -lreadline -L ./readline-8.1/lib #-L/usr/local/opt/readline/lib #-I/usr/local/opt/readline/include


#------------------------COLORS------------------------#

DEF_COLOR	= \033[0;39m
GRAY		= \033[0;90m
RED			= \033[0;91m
GREEN		= \033[0;92m
YELLOW		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m
H_RED		= \033[0;101m
RESET		= \033[0m

#------------------------PATH--------------------------#

SRCS_PATH		:= src

OBJS_PATH		:= obj

BUILTINS_PATH	:= builtins

REDIR_PATH		:= redir

LEXER_PATH		:= lexer

SPLITERS_PATH	:= spliters

LIBFT_PATH		:= libft

#------------------------FILES-------------------------#

BUILTINS	= env exit unset export cd echo pwd builtins builtin_utils
REDIR		= redir pipe spliter_utils
LEXER		= lexer lexer_utils expand tokenize syntax
MAIN		= main free error signal execve prompt utils redir

#------------------------------------------------------#

SRCS		:= $(addsuffix .c, $(addprefix $(SRCS_PATH)/$(BUILTINS_PATH)/, $(BUILTINS)))
SRCS		+= $(addsuffix .c, $(addprefix $(SRCS_PATH)/$(REDIR_PATH)/, $(REDIR)))
SRCS		+= $(addsuffix .c, $(addprefix $(SRCS_PATH)/$(LEXER_PATH)/, $(LEXER)))
SRCS		+= $(addsuffix .c, $(addprefix $(SRCS_PATH)/, $(MAIN)))

OBJS		:= $(addsuffix .o, $(addprefix $(OBJS_PATH)/, $(BUILTINS)))
OBJS		+= $(addsuffix .o, $(addprefix $(OBJS_PATH)/, $(REDIR)))
OBJS		+= $(addsuffix .o, $(addprefix $(OBJS_PATH)/, $(LEXER)))
OBJS		+= $(addsuffix .o, $(addprefix $(OBJS_PATH)/, $(MAIN)))

#------------------------------------------------------#

vpath %.c $(SRCS_PATH)/$(BUILTINS_PATH) $(SRCS_PATH)/$(REDIR_PATH)/ $(SRCS_PATH)/$(LEXER_PATH)/ $(SRCS_PATH)/$(SPLITERS_PATH) $(SRCS_PATH)/

$(OBJS_PATH)/%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "$(NEWLINE)$(CYAN)Creating object file $@ from $<"

all:
	@mkdir -p $(OBJS_PATH)
	@make ${NAME}

${NAME} : ${OBJS}
	@printf "$(NEWLINE)$(RESET)\n"
	@make -C $(LIBFT_PATH)
	@${CC} ${CFLAGS} $^ ${READLINE} ${INCLUDE} ${LIB} -o $@
	@echo "$(GREEN)$(NAME) was created$(RESET)"

clean :
	@make fclean -C $(LIBFT_PATH)
	@rm -rf $(OBJS_PATH)
	@echo "$(BLUE)$(NAME): $(CYAN)object files are cleaned$(RESET)"

fclean : clean
	@rm -rf ${NAME}
	@echo "$(BLUE)$(NAME): $(H_RED) $(NAME) was deleted $(RESET)"

re : fclean all

norm :
	norminette libft/ includes/ src/

docker_build:
	docker build -t minishell_image .

docker_run:
	@docker rm -f minishell_container > /dev/null 2>&1
	docker run -dit --name minishell_container -v $(shell pwd):/minishell/ minishell_image
	docker exec minishell_container make
	docker exec -it minishell_container ./minishell
	@docker rm -f minishell_container > /dev/null 2>&1

docker_clean:
	docker rmi -f minishell_image > /dev/null 2>&1

.PHONY: all clean fclean re
