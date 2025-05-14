#include "../minishell.h"

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
		else if (is_quote(line[i]))
		{
			if (handle_quote_part(data, line, &i))
				return (1);
		}
		else
			handle_word_segments(data, line, &i);
	}
	return (0);
}

