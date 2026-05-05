NAME = codexion

SRCS = main.c coder_routine.c time.c parsing.c dongle.c \
	parsing_utils.c utils_second.c heap.c phases.c init.c

OBJS = $(SRCS:.c=.o)

CC = cc
AR = ar
CFLAGS = -Wall -Wextra -Werror -pthread -g

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re