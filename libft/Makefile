SRCS	= ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_memset.c ft_strlen.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
		ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		get_next_line.c

SRCS_BONUS =	./ft_lstnew.c ./ft_lstadd_front.c ./ft_lstsize.c \
				./ft_lstlast.c ./ft_lstadd_back.c ./ft_lstdelone.c \
				./ft_lstclear.c ./ft_lstiter.c ./ft_lstmap.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

NAME = libft.a

CC = gcc

CFLAGS	= -Wall -Werror -Wextra
NEWLINE = \e[1K\r
GREEN = '\033[32m'
RED	= "\033[0;31m"

$(NAME) : ${OBJS}
		@printf "${NEWLINE}"
		@echo $(GREEN)"- Compiled -"$(NONE)
		@ar rcs ${NAME} ${OBJS}

all : $(NAME)

bonus : ${OBJS_BONUS}
		@echo "Making Bonuses..."
		ar rcs ${NAME} ${OBJS_BONUS}

%.o : %.c
		@${CC} ${CFLAGS} -c $<
		@printf "$(NEWLINE)Creating object file $@ from $<"

clean :
		@echo "Cleaning binary files 'libft'..."
		@rm -f ${OBJS} ${OBJS_BONUS}

fclean : clean
		@echo "Cleaning library..."
		@echo $(RED)"- Deleted -"$(NONE)
		@rm -f libft.a

re : fclean all
