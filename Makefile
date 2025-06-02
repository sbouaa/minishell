NAME = minishell
CC = cc
CFLAGS = -I/usr/local/opt/readline/include
LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

SRCS = main.c init_data.c garbage_collector/garbage.c lexer/lexer.c lexer/utils.c \
	lexer/utils_2.c lexer/handler_lexer.c expanding/expand.c syntax_error/syntax_error.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS) -fsanitize=address -g

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all