#include "../minishell.h"

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
