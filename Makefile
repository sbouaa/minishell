NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

SRCS = main.c init_data.c garbage_collector/garbage.c lexer/lexer.c lexer/utils.c lexer/lexer_handle.c parsing/parser.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all