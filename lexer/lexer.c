#include "../minishell.h"

int	is_token(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_space(int c)
{
	return (c == ' ' || c == '\t');
}

int	is_quote(int c)
{
	return (c == '\'' || c == '"');
}

char	*ft_extract_fline(t_data *data, char *line, int start, int end, int add_space)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = end - start + 1;
	if (add_space)
		len++;
	str = gc_malloc(&data->gc, len + 1);
	if (!str)
		return (NULL);
	while (start <= end)
		str[i++] = line[start++];
	if (add_space)
		str[i++] = ' ';
	str[i] = '\0';
	return (str);
}

int	handle_redirection(t_data *data, char *line, int *i)
{
	if (line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '<')
		{
			add_node_to_back(data, HEREDOC, "<<");
			(*i)++;
		}
		else
			add_node_to_back(data, IN_REDIRECT, "<");
	}
	else if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '>')
		{
			add_node_to_back(data, APPEND, ">>");
			(*i)++;
		}
		else
			add_node_to_back(data, OUT_REDIRECT, ">");
	}
	return (0);
}

int	handle_tokens(t_data *data, char *line, int *i)
{
	if (line[*i] == '|')
	{
		add_node_to_back(data, PIPE, "|");
		(*i)++;
	}
	else
		handle_redirection(data, line, i);
	return (0);
}

int	handle_word_part(t_data *data, char *line, int *i)
{
	int		start;
	char	*tmp;
	int		add_space;

	start = *i;
	while (line[*i] && !is_space(line[*i])
		&& !is_token(line[*i]) && !is_quote(line[*i]))
		(*i)++;
	add_space = 0;
	if (line[*i] && is_space(line[*i]))
		add_space = 1;
	tmp = ft_extract_fline(data, line, start, *i - 1, add_space);
	add_node_to_back(data, WORD, tmp);
	return (0);
}

int	handle_quote_part(t_data *data, char *line, int *i)
{
	char	quote;
	int		start;
	char	*tmp;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] != quote)
		return (1);
	tmp = ft_extract_fline(data, line, start, *i - 1, 0);
	if (quote == '\'')
		add_node_to_back(data, SIQUOTE, tmp);
	else
		add_node_to_back(data, DBQUOTE, tmp);
	(*i)++;
	if (line[*i] && is_space(line[*i]))
	{
		add_node_to_back(data, SPACEE, " ");
		(*i)++;
	}
	return (0);
}

int	handle_word_segments(t_data *data, char *line, int *i)
{
	while (line[*i] && !is_space(line[*i]) && !is_token(line[*i]))
	{
		if (is_quote(line[*i]))
		{
			if (handle_quote_part(data, line, i))
				return (1);
		}
		else
			handle_word_part(data, line, i);
	}
	return (0);
}

int	lexer(t_data *data)
{
	int		i;
	char	*line;

	i = 0;
	line = data->prompt;
	data->token_list = NULL;
	while (line[i])
	{
		if (is_token(line[i]))
			handle_tokens(data, line, &i);
		else if (handle_word_segments(data, line, &i))
			return (1);
		i++;
	}
	return (0);
}
