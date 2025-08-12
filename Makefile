NAME = minishell

CC = cc

CFLAGS =  -Wall -Wextra -Werror -I/usr/local/opt/readline/include

LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

HEADER = minishell.h

HEADER2 = exec/helper/helper.h

SRCS =  exec/builtins/ft_echo.c exec/builtins/ft_env.c exec/builtins/ft_unset.c exec/builtins/ft_pwd.c exec/builtins/ft_cd.c \
		exec/builtins/ft_export.c exec/builtins/ft_exit.c exec/builtins/utils.c exec/builtins/utils_1.c exec/builtins/ft_export_utils.c \
		exec/gc/g_collector.c exec/gc/gc_c.c exec/builtins/ft_export_utils_2.c \
		parsing/init_data.c exec/exec/exec.c exec/exec/exec_utils_1.c exec/exec/exec_utils_2.c exec/exec/exec_utils_3.c \
		exec/exec/exec_utils_4.c \
		parsing/lexer/lexer.c parsing/lexer/utils.c main.c main_utils1.c main_utils2.c \
		parsing/lexer/utils_2.c parsing/lexer/handler_lexer.c parsing/lexer/handler_lexer_utils.c parsing/expanding/expand.c \
		parsing/expanding/remove_quotes.c parsing/expanding/expand_utils.c parsing/expanding/expand_utils2.c parsing/expanding/expand_utils3.c parsing/syntax_error/syntax_error.c parsing/syntax_error/syntax_error_utils.c \
		parsing/parse/parse_tokens.c parsing/parse/token_handlers.c parsing/parse/error_handling.c \
		parsing/parse/command_management.c parsing/parse/arguments.c parsing/parse/redirection.c \
		parsing/parse/heredoc.c parsing/parse/heredoc_utils2.c parsing/parse/heredoc_utils1.c \
		exec/helper/ft_bzero.c exec/helper/ft_isalnum.c exec/helper/ft_isalpha.c exec/helper/ft_isascii.c exec/helper/ft_isdigit.c exec/helper/ft_isprint.c \
		exec/helper/ft_strcmp.c exec/helper/ft_memcpy.c exec/helper/ft_memmove.c exec/helper/ft_memset.c exec/helper/ft_strchr.c exec/helper/ft_strlcat.c exec/helper/ft_strlcpy.c \
		exec/helper/ft_strlen.c exec/helper/ft_strrchr.c exec/helper/ft_tolower.c exec/helper/ft_toupper.c exec/helper/ft_strncmp.c exec/helper/ft_memchr.c exec/helper/ft_memcmp.c \
		exec/helper/ft_strnstr.c exec/helper/ft_atoi.c exec/helper/ft_calloc.c exec/helper/ft_strdup.c exec/helper/ft_substr.c exec/helper/ft_strjoin.c exec/helper/ft_strtrim.c exec/helper/ft_split.c \
		exec/helper/ft_itoa.c exec/helper/ft_strmapi.c exec/helper/ft_striteri.c exec/helper/ft_putchar_fd.c exec/helper/ft_putstr_fd.c exec/helper/ft_putendl_fd.c exec/helper/ft_putnbr_fd.c \
		exec/helper/ft_strdup_2.c exec/helper/ft_substr_s.c exec/helper/ft_atoi_s.c exec/helper/ft_strjoin_s.c \


OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o : %.c $(HEADER) $(HEADER2)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OBJS)

fclean :
	$(RM) $(NAME)
	$(RM) $(OBJS)

re : fclean all
