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

	if (!content)
		return (1);
	last = get_last_token(data);
	if (should_concatenate(last, line, pos))
	{
		// Just concatenate without removing quotes
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

	quote = line[*i];
	start = *i;
	(*i)++;

	while (line[*i])
	{
		// If we're in double quotes, preserve single quotes and keep going
		if (quote == '"' && line[*i] == '\'')
		{
			(*i)++;
			continue;
		}
		// Only stop if we find matching quote
		if (line[*i] == quote)
			break;
		(*i)++;
	}

	if (!line[*i])
	{
		data->syntax_error = 1;
		return (1);  // Unclosed quote error
	}

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

	start = *i;
	while (line[*i])
	{
		// Handle $" case specially
		if (*i == start && line[*i] == '$' && line[*i + 1] == '"')
		{
			(*i) += 2;  // Skip $"
			// Keep going until we find the closing quote
			while (line[*i] && line[*i] != '"')
				(*i)++;
			// Check for unclosed quote
			if (!line[*i] || line[*i] != '"')
			{
				data->syntax_error = 1;
				return (1);  // Syntax error: unclosed quote
			}
			(*i)++;  // Skip closing quote
			content = ft_substr(data, line, start, *i - start);
			return (add_or_concat_content(data, content, line, start, WORD));
		}

		// Handle $' case specially
		if (*i == start && line[*i] == '$' && line[*i + 1] == '\'')
		{
			(*i) += 2;  // Skip $'
			// Keep going until we find the closing quote
			while (line[*i] && line[*i] != '\'')
				(*i)++;
			// Check for unclosed quote
			if (!line[*i] || line[*i] != '\'')
			{
				data->syntax_error = 1;
				return (1);  // Syntax error: unclosed quote
			}
			(*i)++;  // Skip closing quote
			content = ft_substr(data, line, start, *i - start);
			return (add_or_concat_content(data, content, line, start, WORD));
		}

		// Stop at pipe or redirections if not in quotes
		if (line[*i] == '|' || line[*i] == '<' || line[*i] == '>')
			break;

		// Stop at spaces
		if (is_space(line[*i]))
			break;

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
