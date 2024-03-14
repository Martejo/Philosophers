NAME		= philo

INCLUDE		= include/

HEADER		= $(INCLUDE)philosopher.h

CC			= clang

CFLAGS		= -Wall -Wextra -Werror -O3 -pthread

SRCS 	=		philosopher.c					\
				\
				srcs/initialization/init.c		\
				\
				srcs/parsing/check_arguments.c	\
				\
				srcs/philo_routine/routine.c	\
				\
				srcs/threads_handler/monitor.c	\
				srcs/threads_handler/threads.c	\
				\
				srcs/utils/utils_print.c		\
				srcs/utils/utils_str.c			\
				srcs/utils/utils_error.c		\
				srcs/utils/utils_time.c			\


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
