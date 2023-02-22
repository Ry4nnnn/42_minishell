# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: welim <welim@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 21:58:29 by welim             #+#    #+#              #
#    Updated: 2023/02/22 16:07:28 by welim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

LIB			:= -Llibft -lft

INCLUDE		:= -I./includes -Ilibft -I./readline-8.1/include

CFLAGS		:= $(INCLUDE) #-fsanitize=address#-Wall -Werror -Wextra

CC			:= gcc -g3

NEWLINE 	= \e[1K\r

READLINE	:= -lreadline -L ./readline-8.1/lib -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include

#-------------------------PATH-------------------------#

SRCS_PATH	:= src

OBJS_PATH	:= obj

BUILTINS_PATH	:= builtins

PARSER_PATH	:= parser

LIBFT_PATH	:= libft

#------------------------------------------------------#

BUILTINS	= env exit unset export
PARSER		= pwd
MAIN		= main

#------------------------------------------------------#

SRCS		:= $(addsuffix .c, $(addprefix $(SRCS_PATH)/$(BUILTINS_PATH)/, $(BUILTINS)))
SRCS		+= $(addsuffix .c, $(addprefix $(SRCS_PATH)/$(PARSER_PATH)/, $(PARSER)))
SRCS		+= $(addsuffix .c, $(addprefix $(SRCS_PATH)/, $(MAIN)))

OBJS		:= $(addsuffix .o, $(addprefix $(OBJS_PATH)/, $(BUILTINS)))
OBJS		+= $(addsuffix .o, $(addprefix $(OBJS_PATH)/, $(PARSER)))
OBJS		+= $(addsuffix .o, $(addprefix $(OBJS_PATH)/, $(MAIN)))

#------------------------------------------------------#

vpath %.c $(SRCS_PATH)/$(BUILTINS_PATH) $(SRCS_PATH)/$(PARSER_PATH)/ $(SRCS_PATH)/

$(OBJS_PATH)/%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
	@printf "$(NEWLINE)Creating object file $@ from $< ${NEWLINE}"

all:
		@mkdir -p $(OBJS_PATH)
		@make ${NAME}

${NAME} : ${OBJS} 
	@make -C $(LIBFT_PATH)
	@${CC} ${CFLAGS} $^ ${READLINE} ${INCLUDE} ${LIB} -o $@

clean :
	@make clean -C $(LIBFT_PATH)
	@rm -rf $(OBJS_PATH)

fclean : clean
	@make fclean -C $(LIBFT_PATH)
	@rm -rf ${NAME}

re : fclean all

norm :
	norminette libft/ includes/ src/

.PHONY: all clean fclean re
