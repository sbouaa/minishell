#include "../minishell.h"

void	handle_quotes(t_data *data, char *line, int *i, char quote)
{
	int	start;

	start = *i;
	(*i)++;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if(quote == '"')
		add_node_to_back(data, DBQUOTE, ft_extract_fline(data, line, start, *i));
	else 
		add_node_to_back(data, SIQUOTE, ft_extract_fline(data, line, start, *i));
	if (line[*i] == quote)
		(*i)++;
}

void	handle_tokens(t_data *data, char *line, int *i)
{
	if ((line[*i] == '<' || line[*i] == '>') && line[*i + 1] == line[*i])
	{
		add_node_to_back(data, (line[*i] == '<') ? HEREDOC : APPEND,
			ft_extract_fline(data, line, *i, *i + 1));
		(*i) += 2;
	}
	else if (line[*i] == '|')
	{
		add_node_to_back(data, PIPE, ft_extract_fline(data, line, *i, *i));
		(*i)++;
	}
	else if (line[*i] == '<')
	{
		add_node_to_back(data, IN_REDIRECT, ft_extract_fline(data, line, *i,
				*i));
		(*i)++;
	}
	else if (line[*i] == '>')
	{
		add_node_to_back(data, OUT_REDIRECT, ft_extract_fline(data, line, *i,
				*i));
		(*i)++;
	}
}

void	handle_word(t_data *data, char *line, int *i, int start)
{
	while (line[*i] && !is_space(line[*i]) && !is_token(line[*i]))
		(*i)++;
	add_node_to_back(data, WORD, ft_extract_fline(data, line, start, *i - 1));
}
