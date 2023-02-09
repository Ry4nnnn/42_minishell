NAME		= minishell
LIB			= -Llibft -lft
INCLUDE		= -Iincludes -Ilibft -I./readline-8.1/include
CFLAGS		= -Wall -Werror -Wextra
CC			= gcc
RM			= rm
OBJS_DIR	= ./obj
READLINE	= -lreadline -L ./readline-8.1/lib

SRCS		= ${wildcard src/*.c}

P_OBJS		= ${SRCS:src/%.c=${OBJS_DIR}/%.o}

vpath %.c src

all		: ${NAME}

${NAME} : ${P_OBJS} 
	@make -C libft
	${CC} ${CFLAGS} ${LIB} ${READLINE} ${INCLUDE} ${P_OBJS} -o $@

obj/%.o : %.c
	@mkdir -p obj
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

clean :
	@rm -r obj 
	@echo "Cleaning binary files 'minishell'..."

fclean : clean
	@rm -r ${NAME} ${CHECKER}
	@make fclean -C libft

re : fclean all

norm :
	norminette libft/ includes/ src/

.PHONY: all clean fclean re
