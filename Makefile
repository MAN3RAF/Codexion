
NAME = codexion

SRCS = src/main.c \
	   src/coder_routine.c \
	   src/time.c \
	   src/parsing.c \
	   src/dongle.c \
	   src/parsing_utils.c \
	   src/utils.c \
	   src/heap.c \
	   src/compile.c \
	   src/init.c \
	   src/monitor.c \
	   src/clean.c

OBJS = $(SRCS:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -g

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SECONDARY: $(OBJS)
.PHONY: all clean fclean re