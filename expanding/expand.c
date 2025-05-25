#include "../minishell.h"

static int	ft_find_dollar(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

char	*expand_string(t_data *data, char *str, int is_export)
{
	int		i;
	char	*result;
	int		in_single_quotes;
	int		in_double_quotes;
	char	c[2];

	i = 0;
	result = ft_strdup("", data);
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (str && str[i])
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		result = handle_quotes(data, str, &i, result);
		if (str[i] == '$')
		{
			if (str[i + 1] == '\'' && !in_single_quotes && !in_double_quotes)
				result = handle_dollar_single(data, str, &i, result);
			else if (!in_single_quotes)
			{
				char *expanded = process_dollar(data, str, &i);
				if (expanded)
					result = ft_strjoin(result, expanded, data);
			}
			continue;
		}
		if (str[i])
		{
			c[0] = str[i];
			c[1] = '\0';
			result = ft_strjoin(result, c, data);
			i++;
		}
	}
	return (result);
}

char	*remove_quotes_and_dollar(t_data *data, char *str)
{
	char	*result;
	int		i;
	int		j;
	int		len;

	if (!str || !*str)
		return (str);
	len = ft_strlen(str);
	result = ft_strdup(str, data);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] == '$' && i + 1 < len && (str[i + 1] == '"'
			|| str[i + 1] == '\''))
			result = handle_dollar_quotes(data, result, &i, &j);
		else if (str[i] == '"' || str[i] == '\'')
			result = handle_regular_quotes(data, result, &i, &j);
		else
			result[j++] = str[i++];
		if (!result)
			return (NULL);
	}
	result[j] = '\0';
	return (result);
}

void	remove_quotes_from_tokens(t_data *data)
{
	t_token	*current;
	char	*without_quotes;

	current = data->token_list;
	while (current)
	{
		if (current->type == WORD)
		{
			without_quotes = remove_quotes_and_dollar(data, current->value);
			if (without_quotes)
				current->value = without_quotes;
		}
		current = current->next;
	}
}

void	expand(t_data *data)
{
	t_token	*current;
	char	*expanded;
	int		is_export;

	current = data->token_list;
	while (current)
	{
		is_export = 0;
		if (current->prev && current->prev->type == WORD
			&& ft_strcmp(current->prev->value, "export") == 0)
			is_export = 1;
		if (current->type == WORD && ft_find_dollar(current->value) != -1)
		{
			expanded = expand_string(data, current->value, is_export);
			if (!expanded)
			{
				data->syntax_error = 1;
				return ;
			}
			current->value = expanded;
		}
		current = current->next;
	}
	remove_quotes_from_tokens(data);
} 