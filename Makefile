NAME		= minishell
LIB			= -Llibft -lft
INCLUDE		= -Iincludes -Ilibft -I./readline-8.1/include
FLAGS		= -Wall -Werror -Wextra
CC			= gcc
RM			= rm -rf
OBJS_DIR	= ./obj
READLINE	= -lreadline -L ./readline-8.1/lib

SRCS		= ${wildcard src/*.c}

P_OBJS		= ${SRCS:src/%.c=${OBJS_DIR}/%.o}

vpath %.c src

all		: ${NAME}

${NAME} : ${P_OBJS} 
	@make -C libft
	@${CC} ${FLAGS} ${LIB} ${READLINE} ${INCLUDE} ${P_OBJS} -o $@

obj/%.o : %.c
	@mkdir -p obj
	@${CC} ${FLAGS} ${INCLUDE} -c $< -o $@

clean :
	@rm -rf obj 
	@echo "Cleaning binary files 'minishell'..."

fclean : clean
	@rm -rf ${NAME} ${CHECKER}
	@make fclean -C libft

re : fclean all

.PHONY: all clean fclean re