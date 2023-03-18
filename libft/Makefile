# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wangxuerui <wangxuerui@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/11 20:15:17 by wxuerui           #+#    #+#              #
#    Updated: 2023/03/18 14:25:15 by wangxuerui       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


#variables

NAME	= libft.a
CC	= gcc
AR	= ar rcs
HEADER	= -I libft.h
CFLAGS	= -Wall -Werror -Wextra $(HEADER)
SRCS_DIR	= srcs/
OBJS_DIR	= objs/

#Colors

DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m
RESET = \033[0m

#sources

SRC_FILES	= ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
				ft_strlen ft_strlcpy ft_strlcat ft_toupper ft_tolower ft_strchr ft_strrchr ft_strncmp \
				ft_memset ft_bzero ft_memcpy ft_memmove ft_memchr ft_memcmp ft_strnstr \
				ft_atoi ft_calloc ft_strdup ft_substr ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi ft_striteri \
				ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \
				ft_lstnew ft_lstadd_front ft_lstsize ft_lstlast ft_lstadd_back ft_lstdelone ft_lstclear ft_lstiter ft_lstmap \
				ft_printf ft_print_hex ft_putunsign ft_putvoidptr ft_putcharf ft_putnbrf ft_putstrf ft_get_flags ft_printf_utils ft_putnbrstrf \
				ft_quick_sort ft_2darrlen ft_free2darr \
				get_next_line_bonus get_next_line_utils_bonus \
				ft_strndup ft_strcmp ft_llto2darr ft_strninsert ft_strinsert ft_strjoin_free \
				ft_isnumber

SRCS 		= 	$(addprefix $(SRCS_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJS 		= 	$(addprefix $(OBJS_DIR), $(addsuffix .o, $(SRC_FILES)))

#######

all:
		@mkdir -p $(OBJS_DIR)
		@make $(NAME)

$(OBJS_DIR)%.o:		$(SRCS_DIR)%.c
					@$(CC) $(CFLAGS) -c $< -o $@
					@echo ".\c"

$(NAME):	$(OBJS)
			@echo "\n"
			@$(AR) $(NAME) $(OBJS)
			@echo "$(GREEN)$(NAME) was created$(RESET)"

clean:
		@rm -rf $(OBJS_DIR)
		@echo "$(BLUE)$(NAME): $(YELLOW)object files are cleaned$(RESET)"

fclean:	clean
		@rm -rf $(NAME)
		@echo "$(BLUE)$(NAME): $(MAGENTA)$(NAME) was deleted$(RESET)"

re:	fclean all

.PHONY:	all clean fclean re
