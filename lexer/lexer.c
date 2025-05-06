#include "../minishell.h"

int	is_token(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_space(int c)
{
	return (c == ' ' || c == '\t');
}

char	*ft_extract_fline(t_data *data, char *line, int start, int end)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = end - start + 1;
	str = gc_malloc(&data->gc, len + 1);
	if (!str)
		return (NULL);
	while (start <= end)
		str[i++] = line[start++];
	str[i] = '\0';
	return (str);
}

int	lexer(t_data *data)
{
	int		i;
	char	*line;

	i = 0;
	line = data->prompt;
	data->token_list = NULL;
	data->syntax_error = 0;

	while (is_space(line[i]))
		i++;
	while (line[i])
	{
		if (is_token(line[i]))
			handle_tokens(data, line, &i);
		else
			handle_word(data, line, &i);
		if (data->syntax_error)
			return (1);
		while (is_space(line[i]))
			i++;
	}
	return (0);
}

