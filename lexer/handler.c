#include "../minishell.h"

static int	add_redirection_token(t_data *data, char *line, int *i, char type)
{
	if (type == '<')
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
	else if (type == '>')
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

int	handle_redirection(t_data *data, char *line, int *i)
{
	char type;

	if (!line || !i || *i < 0)
		return (1);
	type = line[*i];
	if (type != '<' && type != '>')
		return (1);
	return (add_redirection_token(data, line, i, type));
}

int	handle_tokens(t_data *data, char *line, int *i)
{
	if (line[*i] == '|')
	{
		add_node_to_back(data, PIPE, "|");
		(*i)++;
	}
	else if (line[*i] == '<')
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

static int is_flag_start(char c)
{
	return (c == '-');
}

static char	*get_word_content(t_data *data, char *line, int start, int end)
{
	if (start > end || !line)
		return (NULL);
	return (ft_substr(data, line, start, end - start + 1));
}

static t_token	*get_last_token(t_data *data)
{
	t_token *last;

	last = data->token_list;
	while (last && last->next)
		last = last->next;
	return (last);
}

static int should_concatenate(t_token *last, char *line, int i)
{
	if (!last)
		return (0);
	if (last->type != WORD && last->type != DBQUOTE && last->type != SIQUOTE)
		return (0);
	if (i > 0 && is_space(line[i - 1]))
		return (0);
	return (1);
}

static int add_or_concat_content(t_data *data, char *content, char *line, int pos, t_token_type type)
{
	t_token *last;
	char *temp;
	int len;

	if (!content)
		return (1);
	last = get_last_token(data);
	if (should_concatenate(last, line, pos))
	{
		// Remove any quotes from the content before concatenating
		len = ft_strlen(content);
		if (len >= 2 && (content[0] == '\'' || content[0] == '"') && 
			content[len - 1] == content[0])
		{
			temp = ft_substr(data, content, 1, len - 2);
			last->value = ft_strjoin(last->value, temp, data);
		}
		else
			last->value = ft_strjoin(last->value, content, data);
		if (!last->value)
			return (1);
	}
	else
		add_node_to_back(data, type, content);
	return (0);
}

int	handle_quote_part(t_data *data, char *line, int *i)
{
	char	quote;
	int		start;
	char	*content;
	int		in_nested_quote;
	char	nested_quote;

	quote = line[*i];
	start = *i;
	(*i)++;
	in_nested_quote = 0;
	while (line[*i])
	{
		if (!in_nested_quote && line[*i] == quote)
			break;
		if (!in_nested_quote && (line[*i] == '\'' || line[*i] == '"'))
		{
			in_nested_quote = 1;
			nested_quote = line[*i];
		}
		else if (in_nested_quote && line[*i] == nested_quote)
			in_nested_quote = 0;
		(*i)++;
	}
	if (!line[*i])
		return (1);
	(*i)++;
	content = ft_substr(data, line, start, *i - start);
	if (!content)
		return (1);
	return (add_or_concat_content(data, content, line, start, WORD));
}

int	handle_word_part(t_data *data, char *line, int *i)
{
	int		start;
	char	*content;
	char    quote_char;
	int     in_quotes;

	start = *i;
	in_quotes = 0;
	while (line[*i] && !is_space(line[*i]) 
		&& line[*i] != '|' && line[*i] != '<' && line[*i] != '>')
	{
		if (line[*i] == '$' && line[*i + 1] && (line[*i + 1] == '\'' || line[*i + 1] == '"'))
		{
			quote_char = line[*i + 1];
			(*i) += 2;  // Skip $ and quote
			// Keep going until we find the matching quote
			while (line[*i] && line[*i] != quote_char)
				(*i)++;
			if (line[*i])
				(*i)++;  // Skip closing quote
			break;
		}
		else if (line[*i] == '\'' || line[*i] == '"')
		{
			// Handle empty quotes
			if (line[*i + 1] && line[*i] == line[*i + 1])
			{
				(*i) += 2;  // Skip empty quotes
				continue;
			}
			if (!in_quotes)
			{
				quote_char = line[*i];
				in_quotes = 1;
			}
			else if (line[*i] == quote_char)
				in_quotes = 0;
			(*i)++;
		}
		else
			(*i)++;
	}
	content = ft_substr(data, line, start, *i - start);
	return (add_or_concat_content(data, content, line, start, WORD));
}

int	handle_word_segments(t_data *data, char *line, int *i)
{
	while (line[*i] && !is_space(line[*i]) && line[*i] != '|' 
		&& line[*i] != '<' && line[*i] != '>')
	{
		if (is_quote(line[*i]))
		{
			if (handle_quote_part(data, line, i))
				return (1);
		}
		else
		{
			if (handle_word_part(data, line, i))
				return (1);
		}
	}
	return (0);
}
