NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -I/usr/local/opt/readline/include #-g3 -fsanitize=address

#CFLAGS = -I/usr/local/opt/readline/include -g

LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

HEADER = minishell.h

HEADER2 = exec/libft/libft.h

LIBFT = exec/libft/libft.a

SRCS =  exec/builtins/ft_echo.c exec/builtins/ft_env.c exec/builtins/ft_unset.c exec/builtins/ft_pwd.c exec/builtins/ft_cd.c \
		exec/builtins/ft_export.c exec/builtins/ft_exit.c exec/builtins/utils.c exec/builtins/utils_1.c exec/builtins/ft_export_utils.c \
		exec/gc/g_collector.c  exec/builtins/ft_export_utils_2.c \
		parsing/init_data.c exec/exec/exec.c exec/exec/exec_utils_1.c exec/exec/exec_utils_2.c exec/exec/exec_utils_3.c\
		parsing/lexer/lexer.c parsing/lexer/utils.c main.c \
		parsing/lexer/utils_2.c parsing/lexer/utils_3.c parsing/lexer/handler_lexer.c parsing/expanding/expand.c \
		parsing/expanding/remove_quotes.c parsing/syntax_error/syntax_error.c parsing/parse/parsing.c \


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
