#include "../minishell.h"

int	is_token(char c) { return (c == '|' || c == '<' || c == '>'); }
int	is_space(int c) { return (c == ' ' || c == '\t'); }
int	is_quote(int c) { return (c == '\'' || c == '"'); }

char	*ft_extract_fline(t_data *data, char *line, int start, int end)
{
	char	*str;
	int		i = 0;

	str = gc_malloc(&data->gc, end - start + 2);
	if (!str)
		return (NULL);
	while (start <= end)
		str[i++] = line[start++];
	str[i] = '\0';
	return (str);
}

int	handle_redirection(t_data *data, char *line, int *i)
{
	if (line[*i] == '<')
	{
		(*i)++;
		if (line[*i] == '<')
			add_node_to_back(data, HEREDOC, "<<"), (*i)++;
		else
			add_node_to_back(data, IN_REDIRECT, "<");
	}
	else if (line[*i] == '>')
	{
		(*i)++;
		if (line[*i] == '>')
			add_node_to_back(data, APPEND, ">>"), (*i)++;
		else
			add_node_to_back(data, OUT_REDIRECT, ">");
	}
	return (0);
}

int	handle_tokens(t_data *data, char *line, int *i)
{
	if (line[*i] == '|')
		add_node_to_back(data, PIPE, "|"), (*i)++;
	else
		handle_redirection(data, line, i);
	return (0);
}

int	handle_word_part(t_data *data, char *line, int *i)
{
	int		start = *i;
	char	*tmp;

	while (line[*i] && !is_space(line[*i])
		&& !is_token(line[*i]) && !is_quote(line[*i]))
		(*i)++;
	tmp = ft_extract_fline(data, line, start, *i - 1);
	add_node_to_back(data, WORD, tmp);
	return (0);
}

int	handle_quote_part(t_data *data, char *line, int *i)
{
	char	quote = line[(*i)++];
	int		start = *i;
	char	*tmp;

	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] != quote)
		return (printf("Error: Unclosed quote\n"), 1);
	tmp = ft_extract_fline(data, line, start, *i - 1);
	if (quote == '\'')
		add_node_to_back(data, SIQUOTE, tmp);
	else
		add_node_to_back(data, DBQUOTE, tmp);
	(*i)++;
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
	int		i = 0;
	char	*line = data->prompt;

	data->token_list = NULL;
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (is_token(line[i]))
			handle_tokens(data, line, &i);
		else if (handle_word_segments(data, line, &i))
			return (1);
	}
	return (0);
}
