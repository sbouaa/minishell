NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -I/usr/local/opt/readline/include -g -fsanitize=address

#CFLAGS = -I/usr/local/opt/readline/include -g

LDFLAGS = -L/usr/local/opt/readline/lib -lreadline

HEADER = minishell.h

HEADER2 = libft/libft.h

LIBFT = libft/libft.a

SRCS = exec.c ft_echo.c ft_env.c ft_unset.c ft_pwd.c ft_cd.c \
		ft_export.c ft_exit.c utils.c utils_1.c ft_export_utils.c \
		

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