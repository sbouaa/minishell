/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:09:25 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/22 08:18:52 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*create_heredoc_filename(void)
{
	static int	heredoc_count = 0;
	char		*number;
	char		*filename;

	number = ft_itoa(heredoc_count++);
	if (!number)
		return (NULL);
	filename = ft_strjoin("/tmp/.heredoc_", number);
	return (filename);
}

static int	write_heredoc_content(int fd, char *delimiter, t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			break;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			break;
		}
		line = expand(line, data->env, data);
		ft_putendl_fd(line, fd);
	}
	return (0);
}

int	handle_heredoc(t_data *data, t_redirection *redir)
{
	char	*filename;
	int		fd;

	filename = create_heredoc_filename();
	if (!filename)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		return (-1);
	}
	if (write_heredoc_content(fd, redir->file, data) != 0)
	{
		close(fd);
		unlink(filename);
		return (-1);
	}
	close(fd);
	redir->file = filename;
	return (0);
} 