#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>

typedef struct s_node
{
	void			*ptr;
	struct s_node	*next;
}					t_node;

typedef struct s_gc
{
	t_node			*head;
}					t_gc;

void				*gc_malloc(t_gc *gc, unsigned int size);
void				gc_add(t_gc *gc, void *ptr);
void				gc_free_all(t_gc *gc);

typedef enum e_token_type
{
	PIPE,
	IN_REDIRECT,
	OUT_REDIRECT,
	HEREDOC,
	APPEND,
	DBQUOTE,
	SIQUOTE,
	WORD
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_arg
{
	char			*value;
	struct s_arg	*next;
}					t_arg;

typedef struct s_cmd
{
	t_arg			*args;
	char			*input_file;
	char			*output_file;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_data
{
	char			*prompt;
	t_token			*token_list;
	t_cmd			*cmd;
	int 			syntax_error;
	t_gc			gc;
}					t_data;

int					init_data(t_data *data);
int					lexer(t_data *data);
int					is_token(char c);
int					is_space(int c);
int					is_token(char c);
char				*ft_substr(t_data *data, const char *s, int start, int len);
char				*ft_strdup(const char *s1, t_data *data);
size_t				ft_strlen(const char *str);
char				*ft_strjoin(const char *s1, const char *s2, t_data *data);
t_token				*create_token(t_data *data, t_token_type type,
						const char *value);
void				add_node_to_back(t_data *data, t_token_type type,
						const char *value);
void				handle_tokens(t_data *data, char *line, int *i);
void				handle_word(t_data *data, char *line, int *i,  int start);
void	handle_quotes(t_data *data, char *line, int *i, char quote);
char				*ft_extract_fline(t_data *data, char *line, int start,
						int end);
void				print_tokens(t_data *data);
char				*get_token_type_string(t_token_type type);
#endif
