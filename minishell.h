#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
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

typedef enum e_token_type
{
	PIPE,
	IN_REDIRECT,
	OUT_REDIRECT,
	HEREDOC,
	APPEND,
	WORD,
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
	bool			ambiguous;
}					t_token;

typedef struct s_redirection {
    t_token_type type;
    char *file;
    int fd;
    struct s_redirection *next;
} t_redirection;

// Command structure
typedef struct s_command {
    char **args;
    t_redirection *redirects;
    int fd_in;
    int fd_out;
    struct s_command *next;
} t_command;


typedef struct s_data
{
	char			*prompt;
	t_token			*token_list;
	t_command	 	*commands;
	int				syntax_error;
	int				exit_status;
	t_gc			gc;
}					t_data;

typedef struct s_quote_ctx
{
	int				i;
	int				start;
	int				was_quoted;
	int				in_single;
	int				in_double;
	char			*result;
}					t_quote_ctx;

/* Core Functions */
int					init_data(t_data *data);

/* Memory Management */
void				*gc_malloc(t_gc *gc, unsigned int size);
void				gc_add(t_gc *gc, void *ptr);
void				gc_free_all(t_gc *gc);

/* String Utils */
size_t				ft_strlen(const char *str);
char				*ft_strdup(const char *s1, t_data *data);
char				*ft_substr(t_data *data, const char *s, int start, int len);
char				*ft_strjoin(const char *s1, const char *s2, t_data *data);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_isalnum(int c);
/* Character Checking */
int					is_token(char c);
int					is_space(int c);
int					is_quote(int c);
int					ft_isalnum(int c);
int					skip_spaces(char *line, int *i);

/* Token Management */
void				add_node_to_back(t_data *data, t_token_type type,
						const char *value);
void				print_token_list(t_data *data);
char				*get_token_type_string(t_token_type type);

/* Lexer Functions */
int					lexer(t_data *data);

/* Handler Lexer Functions */
void				handle_redirections(t_data *data, char *line, int *i);
void				handle_token(t_data *data, char *line, int *i);
int					check_quote_syntax(char *line, int start, int end);
int					handle_word(t_data *data, char *line, int *i);
void				expand(t_data *data);
int					check_syntax_errors(t_data *data);
char				*quote_remove(t_data *data, char *str);
t_command	*parse_tokens(t_data *data);
t_command *parse_tokens(t_data *data);
t_command *parse_command(t_data *data, t_command **head, t_command *current_command);
void parse_redirection(t_data *data, t_command *cmd, t_token *current);
t_command *parse_pipe(t_data *data, t_command *current_command);
void *gc_malloc(struct s_gc *gc, unsigned int size);
void *gc_realloc(struct s_gc *gc, void *ptr, size_t size);
void ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	add_argument(t_data *data, t_command *cmd, char *value);
#endif
