NAME		= philo

INCLUDE		= include/

HEADER		= $(INCLUDE)philosopher.h

CC			= clang

CFLAGS		= -Wall -Wextra -Werror

SRCS 	=		philosopher.c					\
				src/parsing/check_arguments.c	\
				src/utils/utils_print.c			\
				src/utils/utils_str.c			\

OBJS    = ${SRCS:.c=.o}

_CLEAR	= \033[0K\r\c
_OK	= [\033[32mOK\033[0m]

all :  $(NAME)


${NAME}: ${OBJS} $(LIBFT_A)
	@${CC} ${CFLAGS} -g3 -I include  -o $@ $^
	@echo "$(_OK) $(NAME) compiled"

%.o: %.c  include/philosopher.h
	@echo "[..] $(NAME_SHORT)... compiling $*.c\r\c"
	@${CC} ${CFLAGS} -g3 -Iinclude  -c $< -o $@
	@echo "$(_CLEAR)"

clean :
	@$(RM) $(OBJS)
	@$(RM) $(OBJS_BONUS)

fclean : clean
	@$(RM) $(NAME)
	@$(RM) $(NAME_BONUS)

re : fclean all

.PHONY: all clean fclean re 
