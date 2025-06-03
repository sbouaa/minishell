#ifndef MINISHELL_H
# define MINISHELL_H

# include <ctype.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>
# include <stdio.h>
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
	bool ambiguous;
}					t_token;

typedef struct s_data
{
	char			*prompt;
	t_token			*token_list;
	int				syntax_error;
	int				exit_status;
	t_gc			gc;
}					t_data;

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
char				*ft_strtrim(char *s1, char *set, t_data *data);
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
int					expand(t_data *data);
int					check_syntax_errors(t_data *data);

#endif
