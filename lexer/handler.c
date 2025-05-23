#include "../minishell.h"

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
	if (line[*i] == '$')
	{
		if (is_space(line[*i + 1]))
			add_node_to_back(data, EXPAND, "$ ");
		else
			add_node_to_back(data, EXPAND, "$");
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
	while (line[*i] && !is_space(line[*i]) && !is_token(line[*i])
		&& !is_quote(line[*i]))
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
		return (printf("Syntax error: unclosed quote\n"), 1);
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
	while (line[*i])
	{
		if (is_space(line[*i]) || is_token(line[*i]))
			break ;
		if (is_quote(line[*i]))
		{
			if (handle_quote_part(data, line, i))
				return (1);
		}
		else
		{
			handle_word_part(data, line, i);
		}
	}
	return (0);
}
