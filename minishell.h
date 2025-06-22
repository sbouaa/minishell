/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:21:46 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/22 18:59:30 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <fcntl.h>
# include "exec/libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

#define DEF_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"

typedef struct s_col
{
	void			*ptr;
	struct s_col	*next;
}t_col;

typedef enum e_call
{
	FREE,
	MALLOC
}t_call;


t_col	*new_node_s(void	*ptr);
t_col	*last_node_s(t_col **head);
void	add_back_s(t_col	**head, t_col *new);
void	clear_all_s(t_col **head);
void	*gc_malloc(size_t size, t_call call);
///////////////////////////////////////////////////
t_col	*new_node(void	*ptr);
t_col	*last_node(t_col **head);
void	add_back(t_col	**head, t_col *new);
void	clear_all(t_col **head);
void	*g_malloc(size_t size, t_call call);

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_node
{
	void					*ptr;
	struct s_node			*next;
}							t_node;

typedef struct s_gc
{
	t_node					*head;
}							t_gc;

typedef enum e_token_type
{
	PIPE,
	IN_REDIRECT,
	OUT_REDIRECT,
	HEREDOC,
	APPEND,
	WORD,
}							t_token_type;

typedef struct s_token
{
	t_token_type			type;
	char					*value;
	struct s_token			*next;
	struct s_token			*prev;
	bool					ambiguous;
}							t_token;

typedef struct s_redirection
{
	t_token_type			type;
	char					*file;
	int						fd;
	struct s_redirection	*next;
}							t_redirection;

// Command structure
typedef struct s_command
{
	char					**args;
	t_redirection			*redirects;
	int						fd_in;
	int						fd_out;
	int						exit_status;
	struct s_command		*next;
}							t_command;

typedef struct s_data
{
	char					*prompt;
	t_token					*token_list;
	t_command				*commands;
	int						syntax_error;
	int						exit_status;
	t_gc					gc;
	t_env					*env;
}							t_data;

typedef struct s_quote_ctx
{
	int						i;
	int						start;
	int						was_quoted;
	int						in_single;
	int						in_double;
	char					*result;
}							t_quote_ctx;

typedef struct s_expand
{
	int		i;
	int		in_single;
	int		in_double;
	char	*str;
	char	*result;
	char	*expand;
	char	*temp;
}	t_expand;

typedef struct s_parse_context
{
	t_data		*data;
	t_command	**current_cmd;
	t_command	**head;
	int			*error_flag;
}	t_parse_context;

typedef struct s_dd
{
	int				exit_status;
	t_command		*camds;
	t_env			*env;
}					t_dd;

typedef struct s_pipe
{
    int     prev_fd;
    int     fd[2];
    pid_t   *pids;
    int     cmd_size;
    int     i;
    int     status;
}   t_pipe;

void				echo(char **args);
void				ft_putstr_fd(char *s, int fd);
void				ft_env(t_env *env);
int					pwd(t_env *env);
int					cd(char *dir, t_env	*env);
void				ft_exit(char **args);
int					ft_unset(char **args, t_env **env);
t_env				*init_env(char **envp);
t_env				*def_env(void);
char				*ft_getenv(char *name, t_env *env);
t_env				*add_env_var(char *key, char *value, t_env **env);
t_env				*ft_search_env(char *key, t_env *env);
void				ft_lstadd_back(t_env **lst, t_env *new);
t_env				*ft_lstnew(char *key, char *value);
t_env				*ft_lstnew_s(char *key, char *value);
int					env_del(char *name, t_env **env);
int					ft_export(char **args, t_env	*env);
int					export_var(char *var, t_env *env);
void				pr_error(char *var);
char				*get_key_and_value(char *var, int type);
int					get_type(char *var);
int					is_valid(char *key);
int					var_in_env(char *key, char *var, int type, t_env *env);
int					ft_begin_exec(t_command *cmds, t_env *env);
t_dd				*init_data_exec(t_dd	*data, char	**envp);
int					ft_export_no_args(t_env *env);
t_env				*copy_env(t_env *env);
void				ft_sort_env(t_env   *env);

char				**switch_env_arr(t_env *env);
int                 ft_exec(t_command   *cmds, t_env    **env);
int                 ft_begin_exec(t_command *cmds, t_env *env);
char                *ft_find_path(char  *cmd, t_env **env);
char				*get_path(char *cmd, t_env **env);
int					ft_cmd_size(t_command   *cmd);
int					is_builtin(char *cmd);
int					exec_builtin(t_command *cmd, t_env **env);
int					wait_for_all_processes(pid_t *pids, int count);
void				execute_child_process(t_command *cmd, int prev_fd, int *fd, t_env **env);
int					wait_and_get_status(pid_t pid);
int					exec_cmd(char *path, char **env, t_command *cmd);
int					handle_child(t_command  *cmd, t_pipe    *p, t_env   **env);
int					setup_redirections(t_command *cmd);
int					init_pipe(t_pipe	*p, t_command	*cmd);
int					execute_child_cmd(t_command *cmd, t_env **env);
//
int					multi_pipes(t_command	*cmd, t_env	**env);
int					execute_single(t_command *cmd, t_env **env);
int					check_file(char	*name);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Core Functions */
int							init_data(t_data *data);
char						*ft_substr_m(t_data *data, const char *s, int start, int len);
int							is_token(char c);
int							is_space(int c);
int							is_quote(int c);
int							ft_isalnum(int c);
int							skip_spaces(char *line, int *i);

/* Token Management */
void						add_node_to_back(t_data *data, t_token_type type,
								const char *value);
void						print_token_list(t_data *data);
char						*get_token_type_string(t_token_type type);

/* Lexer Functions */
int							lexer(t_data *data);

/* Handler Lexer Functions */
void						handle_redirections(t_data *data, char *line,
								int *i);
void						handle_token(t_data *data, char *line, int *i);
int							check_quote_syntax(char *line, int start, int end);
int							handle_word(t_data *data, char *line, int *i);
void						expand(t_data *data);
int							check_syntax_errors(t_data *data);
char						*quote_remove(t_data *data, char *str);
t_command					*parse_tokens(t_data *data);
t_command					*parse_tokens(t_data *data);
t_command					*parse_command(t_data *data, t_command **head,
								t_command *current_command);
int     parse_redirection(t_data *data, t_command *cmd, t_token *current);
t_command					*parse_pipe(t_data *data,
								t_command *current_command);
void						ft_bzero(void *s, size_t n);
void						add_argument(t_data *data, t_command *cmd,
								char *value);
#endif
