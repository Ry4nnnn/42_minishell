# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welim <welim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 21:58:29 by welim             #+#    #+#              #
#    Updated: 2023/02/16 19:22:04 by welim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

LIB			:= -Llibft -lft

INCLUDE		:= -I./includes -Ilibft -I./readline-8.1/include

CFLAGS		:= #-fsanitize=address#-Wall -Werror -Wextra

CC			:= gcc -g3

RM			:= rm -rf

READLINE	:= -lreadline -L ./readline-8.1/lib

SRCS_PATH	:= ./src

OBJS_PATH	:= ./obj

NEWLINE 	= \e[1K\r

#------------------------------------------------------#

# SRCS		:=	main.c \
# 				builtins/env.c \
# 				builtins/exit.c \
# 				builtins/pwd.c \
# 				builtins/

BUILTINS	= env exit pwd unset

SRCS		:= $(addsuffix .c, $(addprefix src/builtins/, $(BUILTINS))) src/main.c

OBJS		:= $(SRCS:.c=.o)

%.o: %.c
	@mkdir -p obj
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "$(NEWLINE)Creating object file $@ from $<"

all		: ${NAME}

${NAME} : ${OBJS} 
	@make -C libft
	@${CC} ${CFLAGS} $^ ${READLINE} ${INCLUDE} ${LIB} -o $@

clean :
	@make clean -C libft
	@${RM} ${OBJS}
	@${RM} obj

fclean : clean
	@make fclean -C libft
	@rm -r ${NAME}

re : fclean all

norm :
	norminette libft/ includes/ src/

.PHONY: all clean fclean re
