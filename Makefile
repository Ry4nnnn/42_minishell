# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welim <welim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 21:58:29 by welim             #+#    #+#              #
#    Updated: 2023/04/05 15:51:47 by welim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

LIB			:= -Llibft -lft

INCLUDE		:= -I./includes -Ilibft/srcs -I./readline-8.1/include

CFLAGS		:= $(INCLUDE) -fcommon -Wall -Wextra -Werror

ifeq ($(DB), 1)
	CFLAGS	+= -fsanitize=address -g3
endif

ifeq ($(LK), 1)
	CFLAGS	+= -fsanitize=leak -g3
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

EXEC_PATH		:= executor

LIBFT_PATH		:= libft

#------------------------FILES-------------------------#

BUILTINS	= env env_utils exit unset export cd echo pwd builtins builtin_utils
REDIR		= redir pipe heredoc redir_utils redir_utils2 get_iofile
LEXER		= lexer lexer_utils expand tokenize syntax wildcard wildcard_utils
MAIN		= main free error signal prompt utils init
EXEC		= executor executor_utils executor_path_utils handler handler_utils

#------------------------------------------------------#

SRCS		:= $(addsuffix .c, $(addprefix $(SRCS_PATH)/$(BUILTINS_PATH)/, $(BUILTINS)))
SRCS		+= $(addsuffix .c, $(addprefix $(SRCS_PATH)/$(REDIR_PATH)/, $(REDIR)))
SRCS		+= $(addsuffix .c, $(addprefix $(SRCS_PATH)/$(LEXER_PATH)/, $(LEXER)))
SRCS		+= $(addsuffix .c, $(addprefix $(SRCS_PATH)/$(EXEC_PATH)/, $(EXEC)))
SRCS		+= $(addsuffix .c, $(addprefix $(SRCS_PATH)/, $(MAIN)))

OBJS		:= $(addsuffix .o, $(addprefix $(OBJS_PATH)/, $(BUILTINS)))
OBJS		+= $(addsuffix .o, $(addprefix $(OBJS_PATH)/, $(REDIR)))
OBJS		+= $(addsuffix .o, $(addprefix $(OBJS_PATH)/, $(LEXER)))
OBJS		+= $(addsuffix .o, $(addprefix $(OBJS_PATH)/, $(EXEC)))
OBJS		+= $(addsuffix .o, $(addprefix $(OBJS_PATH)/, $(MAIN)))

#------------------------------------------------------#

vpath %.c $(SRCS_PATH)/$(BUILTINS_PATH) $(SRCS_PATH)/$(REDIR_PATH)/ $(SRCS_PATH)/$(LEXER_PATH)/ $(SRCS_PATH)/$(EXEC_PATH) $(SRCS_PATH)/

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

ms_re:
	rm -rf $(OBJS_PATH)
	rm -rf ${NAME}
	make all

norm :
	norminette libft/ includes/ src/

docker_build:
	docker build -t minishell_image .

docker_run:
	@docker rm -f minishell_container > /dev/null 2>&1
	docker run -dit --name minishell_container -v $(shell pwd):/home/wxuerui/Desktop/minishell minishell_image
	docker exec minishell_container make LK=1
	docker exec -it minishell_container bash
	@docker rm -f minishell_container > /dev/null 2>&1

docker_clean:
	docker system prune
	docker rmi -f minishell_image > /dev/null 2>&1

.PHONY: all clean fclean re
