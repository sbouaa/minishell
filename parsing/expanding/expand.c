#include "../../minishell.h"

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

char	*handle_variable_expansion(t_data *data, char *str, int *i,
		int in_single, int in_dbquote, t_token *token)
{
	char	*var_name;
	char	*value;
	int		start;

	in_dbquote = 0;
	if (!in_single && str[*i] == '$')
	{
		(*i)++;
		if (str[*i] == '?')
        {
            (*i)++;
            return (ft_itoa(data->exit_status));
        }
		start = *i;
		while (str[*i] && ft_isalnum(str[*i]))
			(*i)++;
		var_name = ft_substr_m(data, str, start, *i - start);
		value = ft_getenv(var_name, data->env);
		if (!value)
		{
			if (token->prev != NULL && (token->prev->type == IN_REDIRECT
					|| token->prev->type == OUT_REDIRECT
					|| token->prev->type == APPEND))
				token->ambiguous = true;
			value = "";
		}
		return (ft_strdup(value));
	}
	return (NULL);
}
/*
void	ft_check_expand(t_data *data, t_token *token)
{
	int		i;
	int		in_single_quote;
	int		in_double_quote;
	char	*str;
	char	*result;
	char	*expand;
	char	*temp;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	str = token->value;
	result = ft_strdup("");
	while (str && str[i])
	{
		update_quote_states(str[i], &in_single_quote, &in_double_quote);
		if (str[i] == '$' && !in_single_quote)
		{
			if (str[i + 1] && ft_strchr("\'\"", str[i + 1]) && !in_double_quote)
			{
				i++;
				continue ;
			}
			else if (str[i + 1] && ft_isalnum(str[i + 1]))
			{
				expand = handle_variable_expansion(data, str, &i,
						in_single_quote, in_double_quote, token);
				if (expand)
				{
					temp = ft_strjoin(result, expand);
					result = temp;
					continue ;
				}
			}
			else if (str[i + 1] && !ft_isalnum(str[i + 1]))
			{
				temp = ft_strjoin(result, ft_substr_m(data, &str[i], 0, 1));
				result = temp;
			}
		}
		else
		{
			temp = ft_strjoin(result, ft_substr_m(data, &str[i], 0, 1));
			result = temp;
		}
		i++;
	}
	token->value = result;
}*/

void	ft_check_expand(t_data *data, t_token *token)
{
    int		i;
    int		in_single_quote;
    int		in_double_quote;
    char	*str;
    char	*result;
    char	*expand;
    char	*temp;

    i = 0;
    in_single_quote = 0;
    in_double_quote = 0;
    str = token->value;
    result = ft_strdup("");
    while (str && str[i])
    {
        update_quote_states(str[i], &in_single_quote, &in_double_quote);
        if (str[i] == '$' && !in_single_quote)
        {
            if (str[i + 1] && ft_strchr("\'\"", str[i + 1]) && !in_double_quote)
            {
                i++;
                continue ;
            }
            // Accept both alnum and '?' for expansion
            else if (str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '?'))
            {
                expand = handle_variable_expansion(data, str, &i,
                        in_single_quote, in_double_quote, token);
                if (expand)
                {
                    temp = ft_strjoin(result, expand);
                    result = temp;
                    continue ;
                }
            }
            else if (str[i + 1] && !ft_isalnum(str[i + 1]) && str[i + 1] != '?')
            {
                temp = ft_strjoin(result, ft_substr_m(data, &str[i], 0, 1));
                result = temp;
            }
        }
        else
        {
            temp = ft_strjoin(result, ft_substr_m(data, &str[i], 0, 1));
            result = temp;
        }
        i++;
    }
    token->value = result;
}

void	expand(t_data *data)
{
	t_token	*current;

	current = data->token_list;
	while (current)
	{
		current->ambiguous = false;
		ft_check_expand(data, current);
		current->value = quote_remove(data, current->value);
		current = current->next;
	}
}
