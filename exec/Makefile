NAME = minishell

CC = cc

#CFLAGS = -Wall -Werror -Wextra -I/usr/local/opt/readline/include -g -fsanitize=address

CFLAGS = -I/usr/local/opt/readline/include -g

LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

HEADER = builtins/minishell.h

HEADER2 = libft/libft.h

LIBFT = libft/libft.a

SRCS = builtins/exec.c builtins/ft_echo.c builtins/ft_env.c builtins/ft_unset.c builtins/ft_pwd.c builtins/ft_cd.c \
		builtins/ft_export.c builtins/ft_exit.c builtins/utils.c builtins/utils_1.c builtins/ft_export_utils.c \
		gc/g_collector.c \


OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

$(LIBFT) :
	make all -C libft/

%.o : %.c $(HEADER) $(HEADER2)
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	make clean -C libft/
	$(RM) $(OBJS)

fclean :
	make fclean -C libft/
	$(RM) $(NAME)
	$(RM) $(OBJS)

re : fclean all