/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:09:28 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:52:03 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	process_heredoc_line(char *line, char *delimiter,
				t_data *data, bool is_quoted)
{
	char	*content;

	if (!line)
	{
		ft_putstr_fd("minishell: warning: here-document at EOF \n", 2);
		return (1);
	}
	if (ft_strcmp(line, delimiter) == 0)
		return (1);
	if (is_quoted)
		content = ft_strdup(line);
	else
		content = expand(line, data->env, data);
	ft_putendl_fd(content, data->heredoc_fd);
	free(content);
	return (0);
}

static void	write_heredoc_content(int fd, char *delimiter,
				t_data *data, bool is_quoted)
{
	char	*line;

	setup_heredoc_signals_child();
	data->heredoc_fd = fd;
	while (1)
	{
		line = readline("> ");
		if (process_heredoc_line(line, delimiter, data, is_quoted) || !line)
		{
			free(line);
			break ;
		}
		free(line);
	}
	close(fd);
	exit(0);
}

static int	handle_heredoc_parent(pid_t pid, int *status,
	char *filename, int fd)
{
	setup_heredoc_signals_parent();
	waitpid(pid, status, 0);
	restore_interactive_signals();
	if (WIFSIGNALED(*status) && WTERMSIG(*status) == SIGINT)
	{
		close(fd);
		unlink(filename);
		write(1, "\n", 1);
		return (-1);
	}
	return (0);
}

static int	setup_heredoc_file(char **filename, int *fd)
{
	*filename = create_heredoc_filename();
	if (!*filename)
		return (-1);
	*fd = open(*filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd == -1)
		return (-1);
	return (0);
}

int	handle_heredoc(t_data *data, t_redirection *redir)
{
	char		*filename;
	int			fd;
	pid_t		pid;
	int			status;
	t_token		*delimiter_token;

	data->flag_herdoc = 1;
	if (setup_heredoc_file(&filename, &fd) == -1)
		return (-1);
	delimiter_token = find_delimiter_token(data, redir->file);
	if (!delimiter_token)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fd);
		return (unlink(filename), -1);
	}
	if (pid == 0)
		write_heredoc_content(fd, redir->file, data, delimiter_token->quoted);
	else if (handle_heredoc_parent(pid, &status, filename, fd) == -1)
		return (data->exit_status = 130, -1);
	data->flag_herdoc = 0;
	redir->file = filename;
	return (close(fd), 0);
}
