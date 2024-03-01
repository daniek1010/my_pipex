NAME = pipex

SRCS = pipex.c pipex_utils1.c pipex_utils2.c pipex_utils3.c ft_split_pipex.c
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
INCLUDE = pipex.h

$(NAME): $(OBJS) $(INCLUDE)

%.o: %.c
		$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re