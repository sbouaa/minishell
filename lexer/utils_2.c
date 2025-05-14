#include "../minishell.h"

int	is_token(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_space(int c)
{
	return (c == ' ' || c == '\t');
}

int	is_quote(int c)
{
	return (c == '\'' || c == '"');
}

char	*ft_extract_fline(t_data *data, char *line, int start, int end, int add_space)
{
	char	*str;
	int		i;
	int		len;

	i = 0;
	len = end - start + 1;
	if (add_space)
		len++;
	str = gc_malloc(&data->gc, len + 1);
	if (!str)
		return (NULL);
	while (start <= end)
		str[i++] = line[start++];
	if (add_space)
		str[i++] = ' ';
	str[i] = '\0';
	return (str);
}
char *get_token_type_string(t_token_type type)
{
    if (type == PIPE)
        return ("PIPE");
    else if (type == IN_REDIRECT)
        return ("IN_REDIRECT");
    else if (type == OUT_REDIRECT)
        return ("OUT_REDIRECT");
    else if (type == HEREDOC)
        return ("HEREDOC");
    else if (type == APPEND)
        return ("APPEND");
    else if (type == WORD)
        return ("WORD");
	else if (type == DBQUOTE)
        return ("DBQUOTE");
	else if (type == SIQUOTE)
        return ("SIQUOTE");
	else if (type == SPACEE)
        return ("SPACEE");
	return "";	
}