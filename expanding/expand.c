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

	(*i)++;
	start = *i;
	
	if (!str[*i] || (!ft_isalnum(str[*i]) && str[*i] != '_'))
		return (ft_strdup("$", data));

	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;

	var_name = ft_substr(data, str, start, *i - start);
	value = expand_env_var(data, var_name);
	
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

static char *handle_before_dollar(t_data *data, char *str, int i, char *result)
{
	char *temp;

	if (i > 0)
	{
		temp = ft_substr(data, str, 0, i);
		result = ft_strjoin(result, temp, data);
	}
	return (result);
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

static char *expand_string(t_data *data, char *str, int is_export)
{
	int i;
	char *result;
	char *expanded;

	i = 0;
	result = ft_strdup("", data);
	
	while (str && str[i])
	{
		if (str[i] == '$')
		{
			result = handle_before_dollar(data, str, i, result);
			expanded = process_dollar(data, str, &i);
			result = ft_strjoin(result, expanded, data);
			str = str + i;
			i = 0;
		}
		else if (is_export && ft_isalnum(str[i]))
		{
			expanded = handle_export_var(data, str, &i);
			if (expanded)
			{
				result = ft_strjoin(result, expanded, data);
				str = str + i;
				i = 0;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (handle_remaining(data, str, i, result));
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
		if ((current->type == WORD || current->type == DBQUOTE) 
			&& ft_find_dollar(current->value) != -1)
		{
			expanded = expand_string(data, current->value, is_export);
			if (expanded)
				current->value = expanded;
		}
		current = current->next;
	}
}

