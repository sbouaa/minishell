#include "../minishell.h"

char	*handle_remaining(t_data *data, char *str, int i, char *result)
{
	char	*temp;

	if (str && *str && i > 0)
	{
		temp = ft_substr(data, str, 0, i);
		result = ft_strjoin(result, temp, data);
	}
	return (result);
}

char	*handle_quotes(t_data *data, char *str, int *i, char *result)
{
	char	quote[2];

	quote[1] = '\0';
	if (str[*i] == '\'' || str[*i] == '"')
	{
		quote[0] = str[*i];
		result = ft_strjoin(result, quote, data);
		(*i)++;
	}
	return (result);
}

char	*handle_dollar_single(t_data *data, char *str,
	int *i, char *result)
{
	int		start;
	char	*content;

	start = *i;
	*i += 2;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	if (start < *i)
	{
		content = ft_substr(data, str, start + 2, *i - (start + 2));
		if (content)
			result = ft_strjoin(result, content, data);
	}
	if (str[*i] == '\'')
		(*i)++;
	return (result);
}

char	*handle_dollar_quotes(t_data *data, char *str, int *i, int *j)
{
	char	*result;
	int		len;
	char	quote;

	len = ft_strlen(str);
	result = str;
	quote = str[*i + 1];
	*i += 2;
	while (*i < len && str[*i] != quote)
		result[(*j)++] = str[(*i)++];
	if (*i >= len || str[*i] != quote)
	{
		free(result);
		data->syntax_error = 1;
		return (NULL);
	}
	(*i)++;
	return (result);
}

char	*handle_regular_quotes(t_data *data, char *str, int *i, int *j)
{
	char	*result;
	int		len;
	char	quote;

	len = ft_strlen(str);
	result = str;
	quote = str[(*i)++];
	while (*i < len && str[*i] != quote)
		result[(*j)++] = str[(*i)++];
	if (*i >= len || str[*i] != quote)
	{
		free(result);
		data->syntax_error = 1;
		return (NULL);
	}
	(*i)++;
	return (result);
} 