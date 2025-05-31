NAME = minishell
CC = cc
CFLAGS = -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

SRCS = main.c init_data.c garbage_collector/garbage.c lexer/lexer.c lexer/utils.c \
	lexer/utils_2.c lexer/handler_lexer.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) -fsanitize=address

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all