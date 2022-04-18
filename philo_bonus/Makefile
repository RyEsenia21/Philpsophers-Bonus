PHILO_BONUS = philo_bonus

CFLAGS  = -Wall -Wextra -Werror

CC   = gcc

HEADER  = philo_bonus.h

RM   = rm -f

SRCS	=	philo_bonus.c utils.c init_alloc.c utils_2.c actions.c

OBJS   = ${SRCS:.c=.o}


all:   ${PHILO_BONUS}

.c.o:
	${CC} ${CFLAGS} -g -pthread -c $< -o ${<:.c=.o}

$(PHILO_BONUS):	$(OBJS)  $(HEADER)
			$(CC) $(OBJS) $(CFLAGS)  -o $(PHILO_BONUS)

clean:
	${RM} ${OBJS} ${OBJS_B}

fclean:  clean
		${RM} ${PHILO_BONUS}

re:   fclean all

.PHONY:  all clean fclean re
