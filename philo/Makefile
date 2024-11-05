
CC = gcc

CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = MAIN/philo_main.c TOOL/eat_think_sleep.c TOOL/everything_init.c TOOL/observe_routine.c TOOL/parce.c TOOL/spawn_philos.c TOOL/time.c TOOL/philo_helper.c

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

.SECONDARY: $(OBJ)