#include "../minishell.h"

int	is_token(char c)
{
	if (c == '\'' || c == '"' || c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	bunny_ears(char *line, int stop, int to_match)
{
	int	start;

	start = stop;
	while (line[start] && line[start] != to_match)
		start++;
	if (line[start] == to_match)
		return (start);
	return (-1);
}

int	find_token_pos(char *line, int *index_pair, t_token_type *type)
{
	int	i;
	int	start;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'))
		i++;
	if (!line[i])
		return (-1);
	start = i;
	if (is_token(line[i]))
	{
		if (line[i] == '\'' || line[i] == '\"')
			return (handle_quotes(line, i, index_pair, type));
		if (line[i] == '<' || line[i] == '>')
			return (handle_redirection(line, i, index_pair, type));
		if (line[i] == '|')
			return (handle_pipe(i, index_pair, type));
	}
	while (line[i] && !is_token(line[i]) && line[i] != ' ' && line[i] != '\t'
		&& line[i] != '\n')
		i++;
	index_pair[0] = start;
	index_pair[1] = i;
	*type = WORD;
	return (0);
}

int	lexer(t_data *data)
{
	int				index_pair[2];
	t_token_type	type;
	char			*line;
	int				offset;
	char			*token_value;

	line = data->prompt;
	offset = 0;
	data->token_list = NULL;
	while (find_token_pos(line + offset, index_pair, &type) != -1)
	{
		token_value = ft_substr(data, line + offset, index_pair[0],
				index_pair[1] - index_pair[0]);
		add_node_to_back(data, type, token_value);
		offset += index_pair[1];
	}
	return (0);
}
