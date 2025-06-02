#include "../minishell.h"

void	update_quote_states(char c, int *in_single, int *in_double)
{
	if (!*in_single && !*in_double && c == '\'')
		*in_single = 1;
	else if (!*in_single && !*in_double && c == '"')
		*in_double = 1;
	else if (*in_single && c == '\'')
		*in_single = 0;
	else if (*in_double && c == '"')
		*in_double = 0;
}

char	*expand_content(t_data *data, char *content)
{
	int		i = 0;
	int		start;
	char	*result = ft_strdup("", data);
	char	*var_name;
	char	*value;
	char	*temp;

	while (content[i])
	{
		if (content[i] == '$' && ft_isalnum(content[i + 1]))
		{
			i++;
			start = i;
			while (content[i] && ft_isalnum(content[i]))
				i++;
			var_name = ft_substr(data, content, start, i - start);
			value = getenv(var_name);
			if (!value)
				value = "";
			temp = ft_strjoin(result, value, data);
			result = temp;
		}
		else
		{
			temp = ft_strjoin(result, ft_substr(data, &content[i], 0, 1), data);
			result = temp;
			i++;
		}
	}
	return (result);
}

char	*expand_quoted_var(t_data *data, char *str, int *i)
{
	int		start;
	char	quote;
	char	*content;
	char	*expanded_content;

	quote = str[*i + 1];
	*i += 2;  // Skip past $" or $'
	start = *i;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	content = ft_substr(data, str, start, *i - start);
	if (str[*i] == quote)
		(*i)++;
	expanded_content = expand_content(data, content);
	return (expanded_content);
}


char	*handle_variable_expansion(t_data *data, char *str, int *i, int in_single, int in_dbquote)
{
	char	*var_name;
	char	*value;
	int		start;

	if (in_single)
		return (NULL); // No expansion inside single quotes
	if (str[*i] == '$')
	{
		(*i)++;
		start = *i;
		while (str[*i] && ft_isalnum(str[*i]))
			(*i)++;
		var_name = ft_substr(data, str, start, *i - start);
		value = getenv(var_name);
		if (!value)
			value = "";
		return (ft_strdup(value, data));
	}

	return (NULL);
}
char	*ft_strchr(const char *str, int c)
{
	int				i;
	unsigned char	ch;

	if (!str)
		return (NULL);
	i = 0;
	ch = c;
	if (ch == '\0')
	{
		i = ft_strlen(str);
		return ((char *)str + i++);
	}
	while (str[i])
	{
		if (str[i] == ch)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}

void	ft_check_expand(t_data *data, t_token *token)
{
	int		i = 0;
	int		in_single_quote = 0;
	int		in_double_quote = 0;
	char	*str = token->value;
	char	*result = ft_strdup("", data);
	char	*expand;
	char	*temp;

	while (str && str[i])
	{
		update_quote_states(str[i], &in_single_quote, &in_double_quote);
		if (str[i] == '$' && str[i + 1] && ft_strchr("\'\"", str[i + 1]) && !in_double_quote && !in_single_quote)
		{
			i++;
			continue;
		}
		else if (str[i] == '$' && str[i + 1] && ft_isalnum(str[i + 1]))
		{
			expand = handle_variable_expansion(data, str, &i, in_single_quote, in_double_quote);
			if (expand)
			{
				temp = ft_strjoin(result, expand, data);
				result = temp;
				continue;
			}
		}
		else if (str[i] == '$' && str[i + 1] && !ft_isalnum(str[i + 1]))
		{
			temp = ft_strjoin(result, ft_substr(data, &str[i], 0, 1), data);
			result = temp;
		}
		else
		{
			temp = ft_strjoin(result, ft_substr(data, &str[i], 0, 1), data);
			result = temp;
		}
		i++;
	}
	token->value = result;
}

int	expand(t_data *data)
{
	t_token	*current = data->token_list;

	while (current)
	{
		ft_check_expand(data, current);
		current = current->next;
	}
	print_token_list(data);
	return (0);
}
