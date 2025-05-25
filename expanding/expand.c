#include "../minishell.h"

static char *expand_env_var(t_data *data, char *var_name)
{
	char *value;

	if (!var_name || !*var_name)
		return (ft_strdup("$", data));
	
	value = getenv(var_name);
	if (!value)
		return (ft_strdup("", data));
	
	return (ft_strdup(value, data));
}

static char *process_dollar(t_data *data, char *str, int *i)
{
	int start;
	char *var_name;
	char *value;
	char pid_str[16];

	start = *i;
	(*i)++;  // Skip the first $

	// Handle $$ - process ID
	if (str[start + 1] == '$')
	{
		(*i)++;  // Skip second $
		snprintf(pid_str, sizeof(pid_str), "%d", getpid());
		return (ft_strdup(pid_str, data));
	}

	// Handle single $ at end or followed by non-variable char
	if (!str[start + 1] || (!ft_isalnum(str[start + 1]) && str[start + 1] != '_'))
		return (ft_strdup("$", data));

	// Extract variable name
	start++;  // Move past $
	while (str[start] && (ft_isalnum(str[start]) || str[start] == '_'))
		start++;

	var_name = ft_substr(data, str, *i, start - *i);
	value = expand_env_var(data, var_name);
	*i = start;  // Update position to end of variable name
	
	return value;
}

static char *handle_export_var(t_data *data, char *str, int *i)
{
	int start;
	char *var_name;
	char *value;

	start = *i;
	while (str[*i] && str[*i] != '=' && str[*i] != ' ' && str[*i] != '$')
		(*i)++;
	if (*i > start)
	{
		var_name = ft_substr(data, str, start, *i - start);
		value = getenv(var_name);
		if (value)
			return (ft_strdup(value, data));
	}
	return (NULL);
}

static char *handle_remaining(t_data *data, char *str, int i, char *result)
{
	char *temp;

	if (str && *str && i > 0)
	{
		temp = ft_substr(data, str, 0, i);
		result = ft_strjoin(result, temp, data);
	}
	return (result);
}

static char *trim_end(t_data *data, char *str)
{
	int len;
	char *result;
	int in_single_quotes;
	int in_double_quotes;
	int i;

	if (!str)
		return (NULL);
	
	len = ft_strlen(str);
	i = len - 1;
	in_single_quotes = 0;
	in_double_quotes = 0;

	// Find last non-space character outside quotes
	while (i >= 0)
	{
		if (str[i] == '\'' && !in_double_quotes)
			in_single_quotes = !in_single_quotes;
		else if (str[i] == '"' && !in_single_quotes)
			in_double_quotes = !in_double_quotes;
		
		if (!in_single_quotes && !in_double_quotes)
		{
			if (!is_space(str[i]))
				break;
		}
		else
			break;
		i--;
	}
	
	result = ft_substr(data, str, 0, i + 1);
	return (result);
}

static char *expand_string(t_data *data, char *str, int is_export)
{
	int i;
	char *result;
	char *expanded;
	int in_single_quotes;
	int in_double_quotes;

	i = 0;
	result = ft_strdup("", data);
	in_single_quotes = 0;
	in_double_quotes = 0;
	
	while (str && str[i])
	{
		// Handle single quoted dollar sign: '$'
		if (str[i] == '\'' && str[i + 1] == '$' && str[i + 2] == '\'' && !in_double_quotes)
		{
			char c[2] = {'$', '\0'};
			result = ft_strjoin(result, c, data);
			i += 3;  // Skip '$'
			continue;
		}

		// Skip empty quotes
		if ((str[i] == '\'' || str[i] == '"') && str[i + 1] == str[i])
		{
			i += 2;
			continue;
		}

		// Case 1: $"..." outside any quotes - preserve content without quotes
		if (str[i] == '$' && str[i + 1] == '"' && !in_single_quotes && !in_double_quotes)
		{
			i += 2;  // Skip $"
			in_double_quotes = 1;  // Treat content as if in double quotes
			// Copy everything until closing quote, preserving spaces
			while (str[i] && str[i] != '"')
			{
				if (str[i] == '$')
				{
					expanded = process_dollar(data, str, &i);
					if (expanded)
						result = ft_strjoin(result, expanded, data);
				}
				else
				{
					char c[2] = {str[i], '\0'};
					result = ft_strjoin(result, c, data);
					i++;
				}
			}
			if (str[i] == '"')
			{
				i++;  // Skip closing quote
				in_double_quotes = 0;
			}
			continue;
		}

		// Case 2: $'...' outside any quotes - preserve content without quotes
		if (str[i] == '$' && str[i + 1] == '\'' && !in_single_quotes && !in_double_quotes)
		{
			i += 2;  // Skip $'
			while (str[i] && str[i] != '\'')
			{
				char c[2] = {str[i], '\0'};
				result = ft_strjoin(result, c, data);
				i++;
			}
			if (str[i] == '\'')
				i++;  // Skip closing quote
			continue;
		}

		// Case 3: Handle single quotes - no expansion inside
		if (str[i] == '\'' && !in_double_quotes)
		{
			in_single_quotes = !in_single_quotes;
			i++;  // Skip the quote
			continue;
		}

		// Case 4: Handle double quotes - allow expansion inside
		if (str[i] == '"' && !in_single_quotes)
		{
			in_double_quotes = !in_double_quotes;
			i++;  // Skip the quote
			continue;
		}

		// Case 5: $$ handling - process ID
		if (str[i] == '$' && str[i + 1] == '$' && !in_single_quotes)
		{
			char pid_str[16];
			snprintf(pid_str, sizeof(pid_str), "%d", getpid());
			result = ft_strjoin(result, pid_str, data);
			i += 2;
			continue;
		}

		// Case 6: Variable expansion inside double quotes or outside quotes
		if (str[i] == '$' && !in_single_quotes)
		{
			expanded = process_dollar(data, str, &i);
			if (expanded)
				result = ft_strjoin(result, expanded, data);
			continue;
		}

		// Case 7: Regular character
		char c[2] = {str[i], '\0'};
		result = ft_strjoin(result, c, data);
		i++;
	}

	return result;
}

static char *remove_quotes_and_dollar(t_data *data, char *str)
{
	char *result;
	int i;
	int j;
	int len;
	
	if (!str || !*str)
		return (str);

	result = ft_strdup(str, data);
	if (!result)
		return (NULL);
	
	i = 0;
	j = 0;
	len = ft_strlen(str);

	while (i < len)
	{
		// Skip empty quotes
		if (i < len - 1 && ((str[i] == '\'' && str[i + 1] == '\'') || 
			(str[i] == '"' && str[i + 1] == '"')))
		{
			i += 2;
			continue;
		}

		// Copy character
		result[j++] = str[i++];
	}

	result[j] = '\0';
	return (result);
}

void	remove_quotes_from_tokens(t_data *data)
{
	t_token *current;
	char *without_quotes;

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

void expand(t_data *data)
{
	t_token *current;
	char *expanded;
	int is_export;

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
			if (expanded)
				current->value = expanded;
		}
		current = current->next;
	}
	// Remove quotes after all expansions are done
	remove_quotes_from_tokens(data);
}

