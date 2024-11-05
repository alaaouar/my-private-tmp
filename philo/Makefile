
CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = philo_main.c eat_think_sleep.c everything_init.c observe_routine.c parce.c spawn_philos.c time.c

OBJS = $(SRCS:.c=.o)

NAME = philo

HEADERS = philo_head.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re