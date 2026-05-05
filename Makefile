NAME = codexion

SRCS = main.c coder_routine.c time.c parsing.c dongle.c \
	parsing_utils.c utils_second.c heap.c compile.c init.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)


debug:
	$(CC) $(CFLAGS) -D DEBUGGING=1 $(SRCS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re