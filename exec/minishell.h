/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 01:43:44 by sbouaa            #+#    #+#             */
/*   Updated: 2025/04/28 16:00:35 by sbouaa           ###   ########.fr       */
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

typedef struct s_dd 
{
	char	**cmd;
	char	**mmd;
	int		in_file;
	int		out_file;
	char	*old_pwd;
	char	*line;
	int		exit_status;
}			t_dd;

void	echo(char *line);
void	ft_putstr_fd(char *s, int fd);
void	env(char	**env);
void	pwd(t_dd	*data);
int		cd(char	*dir, t_dd	*data);
void	ft_exit(char	**cmd);

#endif
