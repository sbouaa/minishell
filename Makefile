NAME = minishell

CC = cc

CFLAGS =  -I/usr/local/opt/readline/include  -Wall -Wextra -Werror -fsanitize=address -g3

LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

HEADER = minishell.h

HEADER2 = exec/libft/libft.h

LIBFT = exec/libft/libft.a

SRCS =  exec/builtins/ft_echo.c exec/builtins/ft_env.c exec/builtins/ft_unset.c exec/builtins/ft_pwd.c exec/builtins/ft_cd.c \
		exec/builtins/ft_export.c exec/builtins/ft_exit.c exec/builtins/utils.c exec/builtins/utils_1.c exec/builtins/ft_export_utils.c \
		exec/gc/g_collector.c exec/gc/gc_c.c exec/builtins/ft_export_utils_2.c \
		parsing/init_data.c exec/exec/exec.c exec/exec/exec_utils_1.c exec/exec/exec_utils_2.c exec/exec/exec_utils_3.c \
		exec/exec/exec_utils_4.c exec/exec/exec_utils_5.c \
		parsing/lexer/lexer.c parsing/lexer/utils.c main.c main_utils1.c main_utils2.c \
		parsing/lexer/utils_2.c parsing/lexer/handler_lexer.c parsing/lexer/handler_lexer_utils.c parsing/expanding/expand.c \
		parsing/expanding/remove_quotes.c parsing/expanding/expand_utils.c parsing/expanding/expand_utils2.c parsing/expanding/expand_utils3.c parsing/syntax_error/syntax_error.c parsing/syntax_error/syntax_error_utils.c \
		parsing/parse/parse_tokens.c parsing/parse/token_handlers.c parsing/parse/error_handling.c \
		parsing/parse/command_management.c parsing/parse/arguments.c parsing/parse/redirection.c parsing/parse/utils.c \
		parsing/parse/heredoc.c parsing/parse/heredoc_utils2.c parsing/parse/heredoc_utils1.c \


OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(LIBFT) :
	make all -C exec/libft/

%.o : %.c $(HEADER) $(HEADER2)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make clean -C exec/libft/
	$(RM) $(OBJS)

fclean :
	make fclean -C exec/libft/
	$(RM) $(NAME)
	$(RM) $(OBJS)

re : fclean all
