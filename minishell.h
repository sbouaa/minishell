#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
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
	WORD,
	SPACEE
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd {
    char    **args;         // Command and its arguments
    int     arg_count;      // Number of arguments
    int     arg_capacity;   // Capacity of the args array
    char    *infile;        // Input redirection file
    char    *outfile;       // Output redirection file
    int     in_type;        // 0 = none, 1 = <, 2 = <<
    int     out_type;       // 0 = none, 1 = >, 2 = >>
    struct s_cmd *next;     // Next command in pipeline
} t_cmd;

typedef struct s_data
{
	char			*prompt;
	t_token			*token_list;
	t_cmd			*cmd_list;
	int 			syntax_error;
	t_gc			gc;
}					t_data;

int					init_data(t_data *data);
int					lexer(t_data *data);
int					is_token(char c);
int					is_space(int c);
int					is_token(char c);
int	is_quote(int c);
char				*ft_substr(t_data *data, const char *s, int start, int len);
char				*ft_strdup(const char *s1, t_data *data);
size_t				ft_strlen(const char *str);
char				*ft_strjoin(const char *s1, const char *s2, t_data *data);
t_token				*create_token(t_data *data, t_token_type type,
						const char *value);
void				add_node_to_back(t_data *data, t_token_type type,
						const char *value);
char *ft_extract_fline(t_data *data, char *line, int start, int end, int add_space);
int	handle_tokens(t_data *data, char *line, int *i);
int	handle_redirection(t_data *data, char *line, int *i);
int	handle_word_part(t_data *data, char *line, int *i);
int	handle_quote_part(t_data *data, char *line, int *i);
int	handle_word_segments(t_data *data, char *line, int *i);
void				print_tokens(t_data *data);
char				*get_token_type_string(t_token_type type);
#endif
