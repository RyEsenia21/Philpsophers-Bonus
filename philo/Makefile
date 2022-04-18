NAME			= philo

SRCS			= main.c \
					arr_pth_create.c \
					atoi.c \
					check_arguments.c \
					function_life.c \
					smart_sleep.c 

OBJS			= $(SRCS:.c=.o)

CC				= gcc

RM				= rm -f

CFLAGS			= -Wall -Wextra -Werror

INCLUDE			= -lpthread

HEADER			= philo.h

all:			$(NAME)

$(NAME):		$(OBJS)
				$(CC) $(OBJS) -o $(NAME)

clean:
				$(RM) $(OBJS) 

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re