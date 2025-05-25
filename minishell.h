#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h>

typedef struct s_node {
	void	*ptr;
	struct s_node *next;
} t_node;

typedef struct s_gc {
	t_node	*head;
} t_gc;

typedef enum e_token_type {
	PIPE,
	IN_REDIRECT,
	OUT_REDIRECT,
	HEREDOC,
	APPEND,
	DBQUOTE,
	SIQUOTE,
	WORD,
	SPACEE,
	EXPAND
} t_token_type;

typedef struct s_token {
	t_token_type	type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
} t_token;

typedef struct s_data {
	char		*prompt;
	t_token		*token_list;
	int			syntax_error;
	t_gc		gc;
} t_data;

/* Core Functions */
int		init_data(t_data *data);

/* Memory Management */
void	*gc_malloc(t_gc *gc, unsigned int size);
void	gc_add(t_gc *gc, void *ptr);
void	gc_free_all(t_gc *gc);

/* String Utils */
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1, t_data *data);
char	*ft_substr(t_data *data, const char *s, int start, int len);
char	*ft_strjoin(const char *s1, const char *s2, t_data *data);
int		ft_strcmp(const char *s1, const char *s2);

/* Character Checking */
int		is_token(char c);
int		is_space(int c);
int		is_quote(int c);
int		ft_isalnum(int c);

/* Token Management */
void	add_node_to_back(t_data *data, t_token_type type, const char *value);
void	print_token_list(t_data *data);
char	*get_token_type_string(t_token_type type);

/* Lexer Functions */
int		lexer(t_data *data);
int		handle_tokens(t_data *data, char *line, int *i);
int		handle_quote_part(t_data *data, char *line, int *i);
int		handle_word_segments(t_data *data, char *line, int *i);
int		handle_word_part(t_data *data, char *line, int *i);

/* Expansion Functions */
void	expand(t_data *data);
int		ft_find_dollar(const char *str);

/* Error Handling */
int		check_syntax_errors(t_data *data);

#endif
