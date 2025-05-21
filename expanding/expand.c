#include "../minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z')
		|| (c >= '0' && c <= '9')
		|| c == '_')
		return (1);
	return (0);
}

int	ft_find_first_non_alnum(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (i);
		i++;
	}
	return (i);
}

int	ft_find_dollar(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	expand_normal(t_data *data, t_token *current)
{
	char	*holder;
	char	*end;
	char	*expanded_value;
	char	*new_value;
	int		non_alnum_index;

	new_value = NULL;
	non_alnum_index = ft_find_first_non_alnum(current->value);
	holder = ft_extract_fline(data, current->value, 0, non_alnum_index - 1, 0);
	expanded_value = getenv(holder);
	if (!expanded_value)
		expanded_value = "";
	end = ft_extract_fline(data, current->value,
			non_alnum_index, ft_strlen(current->value) - 1, 0);
	new_value = ft_strjoin(expanded_value, end, data);
	free(current->value);
	current->value = new_value;
	free(holder);
	free(end);
}

char	*join_expanded(t_data *data, char *new_val, char *first, char *exp)
{
	char	*tmp;
	char	*joined;

	if (!new_val)
		return (ft_strjoin(first, exp, data));
	tmp = ft_strjoin(new_val, first, data);
	free(new_val);
	joined = ft_strjoin(tmp, exp, data);
	free(tmp);
	return (joined);
}

static void	handle_dollar(t_data *data, t_token *cur, char **new_val)
{
	int		start;
	int		index;
	char	*first;
	char	*holder;
	char	*expanded;
	char	*end;

	start = 0;
	index = ft_find_dollar(cur->value);
	first = ft_extract_fline(data, cur->value, start, index - 1, 0);
	start = index + 1;
	while (cur->value[start] && (ft_isalnum(cur->value[start]) || cur->value[start] == '_'))
		start++;
	holder = ft_extract_fline(data, cur->value, index + 1, start - 1, 0);
	expanded = getenv(holder);
	if (!expanded)
		expanded = "";
	*new_val = join_expanded(data, *new_val, first, expanded);
	free(first);
	free(holder);
	end = ft_extract_fline(data, cur->value, start, ft_strlen(cur->value) - 1, 0);
	free(cur->value);
	cur->value = end;
}
static void	expand_var(t_data *d, t_token *cur, int i, char **new_val)
{
	char	*first;
	char	*holder;
	char	*expanded;
	char	*end;
	int		start;

	first = ft_extract_fline(d, cur->value, 0, i - 1, 0);
	start = i + 1;
	if (!cur->value[start]
		|| (!ft_isalnum(cur->value[start]) && cur->value[start] != '_'))
	{
		*new_val = join_expanded(d, *new_val, first, "$");
		free(first);
		end = ft_extract_fline(d, cur->value,
				start, ft_strlen(cur->value) - 1, 0);
		free(cur->value);
		cur->value = end;
		return ;
	}
	while (ft_isalnum(cur->value[start]) || cur->value[start] == '_')
		start++;
	holder = ft_extract_fline(d, cur->value, i + 1, start - 1, 0);
	expanded = getenv(holder);
	if (!expanded)
		expanded = "";
	*new_val = join_expanded(d, *new_val, first, expanded);
	free(first);
	free(holder);
	end = ft_extract_fline(d, cur->value,
			start, ft_strlen(cur->value) - 1, 0);
	free(cur->value);
	cur->value = end;
}


void	expand_dbquote(t_data *d, t_token *cur)
{
	char	*new_val;
	char	*tmp;

	new_val = NULL;
	while (ft_find_dollar(cur->value) != -1)
		expand_var(d, cur, ft_find_dollar(cur->value), &new_val);
	if (cur->value && *cur->value)
	{
		tmp = ft_strjoin(new_val, cur->value, d);
		free(new_val);
		new_val = tmp;
	}
	free(cur->value);
	cur->value = new_val;
}

void	expand(t_data *data)
{
	t_token	*current;

	current = data->token_list;
	while (current)
	{
		if (current->type == EXPAND && current->next != NULL){
            if(current->next->type == WORD && !is_space(current->value[1]))
			    expand_normal(data, current->next);
        }
		if (current->type == DBQUOTE)
			expand_dbquote(data, current);
		current = current->next;
	}
}
