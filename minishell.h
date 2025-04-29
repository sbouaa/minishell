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
	QUOTE,
	WORD
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_cmd {
    char **cmd;
    int n_cmd;
    struct s_cmd *next;
} t_cmd;

typedef struct s_data
{
	char			working_dir[1024];
	char			*prompt;
	t_token			*token_list;
	t_cmd			*command_list;
	struct termios	original_term;
	struct termios	shell_term;
	int				exit_status;
	t_gc			gc;
}					t_data;

int					init_data(t_data *data);
int					lexer(t_data *data);
int					is_token(char c);
int					bunny_ears(char *line, int stop, int to_match);
int					find_token_pos(char *line, int *index_pair,
						t_token_type *type);

char				*ft_substr(t_data *data, const char *s, int start, int len);
char				*ft_strdup(const char *s1, t_data *data);
size_t				ft_strlen(const char *str);
t_token				*create_token(t_data *data, t_token_type type,
						const char *value);
void				add_node_to_back(t_data *data, t_token_type type,
						const char *value);

int					handle_quotes(char *line, int i, int *index_pair,
						t_token_type *type);
int					handle_redirection(char *line, int i, int *index_pair,
						t_token_type *type);
int					handle_pipe(int i, int *index_pair, t_token_type *type);

void				print_tokens(t_data *data);
char				*get_token_type_string(t_token_type type);

void	print_commands(t_cmd *cmd_list);
void parse_command_list(t_data *data);

#endif
