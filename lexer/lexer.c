#include "../minishell.h"

int	is_token(char c)
{
	return (c == '\'' || c == '"' || c == '|' || c == '<' || c == '>');
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
	int		start;
	char	*line;

	i = 0;
	line = data->prompt;
	data->token_list = NULL;
	while (is_space(line[i]))
		i++;
	while (line[i])
	{
		start = i;
		if (line[i] == '\'' || line[i] == '"')
			handle_quotes(data, line, &i, line[i]);
		else if (is_token(line[i]))
			handle_tokens(data, line, &i);
		else
			handle_word(data, line, &i, start);
		while (is_space(line[i]))
			i++;
	}
	return (0);
}
