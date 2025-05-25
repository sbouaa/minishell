#include "../minishell.h"

static int	skip_spaces(char *line, int *i)
{
	while (line[*i] && is_space(line[*i]))
		(*i)++;
	return (0);
}

static int	handle_error(t_data *data, char *error_msg)
{
	data->syntax_error = 1;
	if (error_msg)
		printf("Syntax error: %s\n", error_msg);
	return (1);
}

int	lexer(t_data *data)
{
	int		i;
	char	*line;
	int		had_space;

	if (!data || !data->prompt)
		return (handle_error(data, "invalid input"));
	i = 0;
	line = data->prompt;
	data->token_list = NULL;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break;
		if (is_token(line[i]))
		{
			if (handle_tokens(data, line, &i))
				return (handle_error(data, "invalid token"));
		}
		else if (is_quote(line[i]))
		{
			if (handle_quote_part(data, line, &i))
				return (handle_error(data, "unclosed quote"));
		}
		else
		{
			if (handle_word_segments(data, line, &i))
				return (handle_error(data, "syntax error: unexpected end of input"));
		}
	}
	return (0);
}
