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

static t_token	*find_delimiter_token(t_data *data, char *delimiter)
{
	t_token	*token;

	token = data->token_list;
	while (token)
	{
		if (token->type == HEREDOC && token->next
			&& ft_strcmp(token->next->value, delimiter) == 0)
			return (token->next);
		token = token->next;
	}
	return (NULL);
}

static int	process_heredoc_line(char *line, char *delimiter,
	t_data *data, bool is_quoted)
{
	char	*content;

	if (!line)
	{
		ft_printf("minishell: warning: here-document at EOF\n");
		return (1);
	}
	if (ft_strcmp(line, delimiter) == 0)
		return (1);
	content = is_quoted ? ft_strdup(line) : expand(line, data->env, data);
	ft_putendl_fd(content, data->heredoc_fd);
	return (0);
}

static int	write_heredoc_content(int fd, char *delimiter,
	t_data *data, bool is_quoted)
{
	char	*line;

	data->heredoc_fd = fd;
	while (1)
	{
		line = readline("> ");
		if (process_heredoc_line(line, delimiter, data, is_quoted))
			break ;
	}
	return (0);
}

int	handle_heredoc(t_data *data, t_redirection *redir)
{
	char	*filename;
	int		fd;
	t_token	*delimiter_token;

	filename = create_heredoc_filename();
	if (!filename)
		return (-1);
	delimiter_token = find_delimiter_token(data, redir->file);
	if (!delimiter_token)
		return (-1);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (-1);
	if (write_heredoc_content(fd, redir->file, data, delimiter_token->quoted) != 0)
	{
		close(fd);
		unlink(filename);
		return (-1);
	}
	close(fd);
	redir->file = filename;
	return (0);
} 