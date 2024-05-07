NAME		= philo



HEADER		= philo.h

CC			= cc

CFLAGS		= -Wall -Wextra -Werror -pthread

SRCS 	=		main.c		\
				check_args.c	\
				error_handler.c	\
				init_simulation.c	\
				diner_routine.c		\
				init.c				\
				libft_utils.c		\
				monitor.c			\
				mutex_access.c		\
				mutex_handler.c		\
				thread_handler.c	\
				time.c				\
				memory_utils.c		\


OBJS    = ${SRCS:.c=.o}

_CLEAR	= \033[0K\r\c
_OK	= [\033[32mOK\033[0m]

all :  $(NAME)

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} -o $@ $^
	@echo "$(_OK) $(NAME) compiled"

%.o: %.c  $(HEADER)
	@echo "[..] $(NAME)... compiling $*.c\r\c"
	@${CC} ${CFLAGS} -c $< -o $@
	@echo "$(_CLEAR)"
	
clean :
	@$(RM) $(OBJS)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re 
