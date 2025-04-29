/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 01:43:44 by sbouaa            #+#    #+#             */
/*   Updated: 2025/04/29 19:46:46 by sbouaa           ###   ########.fr       */
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
	char	*old_pwd;
	char	*line;
	int		exit_status;
	t_env	*env;
}			t_dd;


//
void	echo(char *line);
void	ft_putstr_fd(char *s, int fd);
void	env(t_dd	*data);
void	pwd(t_dd	*data);
int		cd(char	*dir, t_dd	*data);
void	ft_exit(char	**cmd);

//
t_env	*init_env(char	**envp);

// 
void	mn_lstadd_back(t_env **lst, t_env *new);
t_env	*mn_lstnew(char *key, char *value);
void	ft_clear(t_env	**all);
void	ft_clean(char **p);

#endif
