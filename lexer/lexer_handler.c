#include "../minishell.h"

int check_unclosed_quote(t_data *data, char quote, int *i, char *line)
{
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
	{
		printf("minishell: syntax error: unclosed quote\n");
		data->syntax_error = 1;
		return (1);
	}
	return (0);
}

void handle_quotes(t_data *data, char *line, int *i, char quote)
{
	int start;
	char *token;
	char *tmp;

	token = NULL;
	while (line[*i] == quote)
	{
		start = ++(*i);
		while (line[*i] && line[*i] != quote)
			(*i)++;
		tmp = ft_extract_fline(data, line, start, *i - 1);
		if (!token)
			token = ft_strdup(tmp, data);
		else
			token = ft_strjoin(token, tmp, data);
		if (line[*i] == quote)
			(*i)++;
		else
			break;
	}
	if (quote == '"')
		add_node_to_back(data, DBQUOTE, token);
	else
		add_node_to_back(data, SIQUOTE, token);
}

void handle_tokens(t_data *data, char *line, int *i)
{
	if ((line[*i] == '<' || line[*i] == '>') && line[*i + 1] == line[*i])
	{
		add_node_to_back(data,
						 (line[*i] == '<') ? HEREDOC : APPEND,
						 ft_extract_fline(data, line, *i, *i + 1));
		(*i) += 2;
	}
	else if (line[*i] == '|')
	{
		add_node_to_back(data, PIPE,
						 ft_extract_fline(data, line, *i, *i));
		(*i)++;
	}
	else if (line[*i] == '<')
	{
		add_node_to_back(data, IN_REDIRECT,
						 ft_extract_fline(data, line, *i, *i));
		(*i)++;
	}
	else if (line[*i] == '>')
	{
		add_node_to_back(data, OUT_REDIRECT,
						 ft_extract_fline(data, line, *i, *i));
		(*i)++;
	}
}

static char *parse_quote(t_data *data, char *line, int *i)
{
	int start;
	char quote;
	char *part;

	quote = line[(*i)++];
	start = *i;
	if (check_unclosed_quote(data, quote, i, line))
		return (NULL);
	part = ft_extract_fline(data, line, start, *i - 1);
	if (line[*i] == quote)
		(*i)++;
	return (part);
}

void handle_word(t_data *data, char *line, int *i)
{
	char *token;
	char *part;
	int start;

	token = NULL;
	while (line[*i] && !is_space(line[*i]) && !is_token(line[*i]))
	{
		if (line[*i] == '\'' || line[*i] == '"')
			part = parse_quote(data, line, i);
		else
		{
			start = *i;
			while (line[*i] && !is_space(line[*i]) && !is_token(line[*i]) && line[*i] != '\'' && line[*i] != '"')
				(*i)++;
			part = ft_extract_fline(data, line, start, *i - 1);
		}
		if (data->syntax_error)
			return;
		token = token ? ft_strjoin(token, part, data) : ft_strdup(part, data);
	}
	add_node_to_back(data, WORD, token);
}
