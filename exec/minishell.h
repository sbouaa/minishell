/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 01:43:44 by sbouaa            #+#    #+#             */
/*   Updated: 2025/05/05 04:48:30 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_env
{
	char	*key;
	char	*value;
	struct s_env *next;
}	t_env;

typedef struct s_dd 
{
	char	**cmd;
	char	**mmd;
	int		in_file;
	int		out_file;
	char	*line;
	int		exit_status;
	t_env	*env;
}			t_dd;


//
void	echo(char *line);
void	ft_putstr_fd(char *s, int fd);
void	env(t_dd	*data);
void	pwd(void);
int		cd(char	*dir, t_dd	*data);
void	ft_exit(char	*nb);
int ft_unset(char   **args, t_env   **env);

//
t_env	*init_env(char	**envp);
char	*ft_getenv(char	*name, t_env	*env);

// 
void	ft_lstadd_back(t_env **lst, t_env *new);
t_env	*ft_lstnew(char *key, char *value);
void	ft_clear(t_env	**all);
void	ft_clean(char **p);
int		ft_strcmp(char *s1, char *s2);


//


#endif
