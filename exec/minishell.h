/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 01:43:44 by sbouaa            #+#    #+#             */
/*   Updated: 2025/05/17 00:54:38 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_dd
{
	char			**cmd;
	char			**mmd;
	int				in_file;
	int				out_file;
	char			*line;
	int				exit_status;
	t_env			*env;
}					t_dd;

//
void				echo(char *line);
void				ft_putstr_fd(char *s, int fd);
void				env(t_env *env);
void				pwd(t_env *env);
int					cd(char *dir, t_dd *data);
void				ft_exit(char *nb);
int					ft_unset(char **args, t_env **env);

//
t_env				*init_env(char **envp);
t_env				*def_env(void);
char				*ft_getenv(char *name, t_env *env);
t_env				*add_env_var(char *key, char *value, t_env **env);
t_env				*ft_search_env(char *key, t_env *env);

//
void				ft_lstadd_back(t_env **lst, t_env *new);
void				ft_lstadd_front(t_env **lst, t_env *new);
t_env				*ft_lstnew(char *key, char *value);
void				ft_clear(t_env **all);
void				ft_clean(char **p);

//
int					env_del(char *name, t_env **env);

//
int					ft_export(char **args, t_dd *data);
int					export_var(char *var, t_env *env);
void				pr_error(char *var);
char				*get_key_and_value(char *var, int type);
int					get_type(char *var);
int					is_valid(char *key);
int					var_in_env(char *key, char *var, int type, t_env *env);

#endif
