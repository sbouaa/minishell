/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:21:46 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 20:50:52 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "exec/helper/helper.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <termios.h>

# define DEF_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

extern int	g_signal;

typedef struct s_col
{
	void			*ptr;
	struct s_col	*next;
}					t_col;

typedef enum e_call
{
	FREE,
	MALLOC
}					t_call;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

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
	bool			quoted;
}					t_token;

typedef struct s_redirection
{
	t_token_type			type;
	char					*file;
	int						fd;
	struct s_redirection	*next;
}							t_redirection;

typedef struct s_command
{
	char				**args;
	t_redirection		*redirects;
	int					exit_status;
	struct s_command	*next;
}						t_command;

typedef struct s_data
{
	char		*prompt;
	t_token		*token_list;
	t_command	*commands;
	int			syntax_error;
	int			exit_status;
	t_gc		gc;
	t_env		*env;
	int			heredoc_fd;
	int			flag_herdoc;
}				t_data;

typedef struct s_quote_ctx
{
	int		i;
	int		start;
	int		was_quoted;
	int		in_single;
	int		in_double;
	char	*result;
}			t_quote_ctx;

typedef struct s_expand
{
	int		i;
	int		in_single;
	int		in_double;
	int		to_expand;
	char	*str;
	char	*result;
	char	*expand;
	char	*temp;
}			t_expand;

typedef struct s_parse_context
{
	t_data		*data;
	t_command	**current_cmd;
	t_command	**head;
	int			*error_flag;
}				t_parse_context;

typedef struct s_pipe
{
	int		prev_fd;
	int		fd[2];
	pid_t	*pids;
	int		cmd_size;
	int		i;
	int		status;
}			t_pipe;

typedef struct s_word_info
{
	int	is_export;
	int	has_dollar;
}		t_word_info;

t_col		*new_node_env(void *ptr);
t_col		*last_node_env(t_col **head);
void		add_back_env(t_col **head, t_col *node);
void		clear_all_env(t_col **head);
void		*gc_malloc(size_t size, t_call call);
t_col		*new_node(void *ptr);
t_col		*last_node(t_col **head);
void		add_back(t_col **head, t_col *node);
void		clear_all(t_col **head);
void		*g_malloc(size_t size, t_call call);
void		echo(char **args);
void		ft_putstr_fd(char *s, int fd);
void		ft_env(t_env *env);
int			pwd(t_env *env);
int			cd(char **args, t_env **env);
void		ft_exit(char **args);
int			ft_unset(char **args, t_env **env);
int			ft_export(char **args, t_env *env);
int			ft_export_no_args(t_env *env);
t_env		*init_env(char **envp);
t_env		*def_env(void);
char		*ft_getenv(char *name, t_env *env);
t_env		*add_env_var(char *key, char *value, t_env **env);
t_env		*ft_search_env(char *key, t_env *env);
void		ft_lstadd_back(t_env **lst, t_env *node);
t_env		*ft_lstnew(char *key, char *value);
t_env		*ft_lstnew_env(char *key, char *value);
int			env_del(char *name, t_env **env);
int			export_var(char *var, t_env *env);
void		pr_error(char *var);
char		*get_key_and_value(char *var, int type);
int			get_type(char *var);
int			is_valid(char *key);
int			var_in_env(char *key, char *var, int type, t_env *env);
t_env		*init_data_exec(char **envp);
t_env		*copy_env(t_env *env);
t_env		*ft_sort_env(t_env *env);
char		*ft_getkey(char *name, t_env *env);
char		*expand_var_value(char *value, t_env *env);
char		**switch_env_arr(t_env *env);
int			ft_exec(t_command *cmds, t_env **env);
int			ft_begin_exec(t_command *cmds, t_env **env);
char		*ft_find_path(char *cmd, t_env **env);
char		*get_path(char *cmd, t_env **env);
int			ft_cmd_size(t_command *cmd);
int			is_builtin(char *cmd);
int			exec_builtin(t_command *cmd, t_env **env);
int			wait_for_all_processes(pid_t *pids, int count);
void		execute_child_process(t_command *cmd, int prev_fd,
				int *fd, t_env **env);
int			wait_and_get_status(pid_t pid);
int			exec_cmd(char *path, char **env, t_command *cmd);
int			handle_child(t_command *cmd, t_pipe *p, t_env **env);
int			setup_redirections(t_command *cmd);
int			init_pipe(t_pipe *p, t_command *cmd);
int			execute_child_cmd(t_command *cmd, t_env **env);
int			multi_pipes(t_command *cmd, t_env **env);
int			execute_single(t_command *cmd, t_env **env);
int			check_file(char *name);
void		close_all(int fd, int flag);
int			init_data(t_data *data);
int			is_token(char c);
int			is_space(int c);
int			is_quote(int c);
int			ft_isalnum(int c);
int			skip_spaces(char *line, int *i);
int			lexer(t_data *data);
void		handle_redirections(t_data *data, char *line, int *i);
void		handle_token(t_data *data, char *line, int *i);
int			check_quote_syntax(char *line, int start, int end);
int			handle_word(t_data *data, char *line, int *i);
int			handle_heredoc_word(t_data *data, char *line, int *i);
int			process_word_char(char *line, int *i, char *current_quote,
				t_word_info *info);
int			handle_error_and_cleanup(t_data *data);
int			is_export_command(t_data *data);
t_token		*add_node_to_back(t_data *data, t_token_type type,
				const char *value);
char		*get_token_type_string(t_token_type type);
t_token		*quote_remove(t_data *data);
t_command	*parse_tokens(t_data *data);
t_command	*parse_command(t_data *data, t_command **head,
				t_command *current_command);
int			parse_redirection(t_data *data, t_command *cmd, t_token *current);
t_command	*parse_pipe(t_data *data, t_command *current_command);
void		add_argument(t_data *data, t_command *cmd, char *value);
int			handle_heredoc(t_data *data, t_redirection *redir);
int			handle_word_token(t_parse_context *ctx, t_token *current);
int			handle_redirection_token(t_parse_context *ctx, t_token *current);
int			is_redirection_token(int type);
t_token		*handle_redirection_parsing(t_parse_context *ctx,
				t_token *current);
t_token		*handle_error_and_skip_to_pipe(t_command **head,
				t_command **current_cmd, t_token *current);
char		*expand(char *prompt, t_env *env, t_data *data);
void		expand_redirections(t_token *token, t_env *env, t_data *data);
void		update_quote_states(char c, int *in_s, int *in_d);
void		process_char(t_expand *exp);
char		*handle_var_expansion(char *str, int *i, t_env *env);
int			is_redirect(char *s, int i);
void		process_dollar(t_expand *exp, t_env *env, t_data *data);
int			is_export_var(char *str);
void		handle_special_dollar(t_expand *exp);
void		handle_quote_dollar(t_expand *exp);
void		expand_loop(t_expand *exp, t_env *env, t_data *data,
				int is_export);
void		handle_exit_status(t_expand *exp, t_data *data);
void		skip_redirect_part(t_expand *exp);
void		skip_redirect_spaces(t_expand *exp);
int			check_syntax_errors(t_data *data);
int			check_pipe_errors(t_token *token);
int			check_redirection_errors(t_token *token);
int			is_redirection(t_token *token);
int			is_word_token(t_token *token);
int			is_valid_heredoc_delimiter(char *delimiter);
int			check_heredoc_errors(t_token *token);
int			handle_prompt(t_data *data, t_env *env);
void		execute_commands(t_data *data);
void		sigint_handler(int sig);
void		free_prompt(t_data *data);
int			handle_empty_line(char *line);
int			handle_lexer_error(t_data *data);
int			dont_display(int set, int value);
void		setup_interactive_signals(void);
void		set_es_signal(int set, t_data *data);
void		sigint_heredoc(int sig);
void		setup_heredoc_signals_child(void);
void		setup_heredoc_signals_parent(void);
void		restore_interactive_signals(void);
char		*create_heredoc_filename(void);
t_token		*find_delimiter_token(t_data *data, char *delimiter);
void		ft_bzero(void *s, size_t n);
void		handle_export_dollar(t_expand *exp, t_env *env, t_data *data);

#endif