/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 21:14:55 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/24 20:04:11 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	in_red(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (ft_printf("minishell: "), perror(file), 1);
    close_all(fd, 0);
	if (dup2(fd, STDIN_FILENO) < 0)
		return (ft_printf("minishell: "), perror("dup2"), close(fd), 1);
	return (close(fd), 0);
}

static int	out_red(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_printf("minishell: "), perror(file), 1);
	close_all(fd, 0);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (ft_printf("minishell: "), perror("dup2"), close(fd), 1);
	return (close(fd), 0);
}

static int	app_red(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ft_printf("minishell: "), perror(file), 1);
	close_all(fd, 0);
	if (dup2(fd, STDOUT_FILENO) < 0)
		return (ft_printf("minishell: "), perror("dup2"), close(fd), 1);
	return (close(fd), 0);
}

static int	red(t_redirection *redir)
{
	if (redir->type == IN_REDIRECT)
		return (in_red(redir->file));
	else if (redir->type == OUT_REDIRECT)
		return (out_red(redir->file));
	else if (redir->type == APPEND)
		return (app_red(redir->file));
	return (0);
}

int	setup_redirections(t_command *cmd)
{
	t_redirection	*redir;

	if (!cmd)
		return (1);
	redir = cmd->redirects;
	while (redir)
	{
		if (red(redir))
			return (1);
		redir = redir->next;
	}
	return (0);
}
