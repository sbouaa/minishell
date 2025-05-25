#include "../minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

char	*expand_env_var(t_data *data, char *var_name)
{
	char	*value;

	if (!var_name || !*var_name)
		return (ft_strdup("$", data));
	value = getenv(var_name);
	if (!value)
		return (ft_strdup("", data));
	return (ft_strdup(value, data));
}

char	*process_dollar(t_data *data, char *str, int *i)
{
	int		start;
	char	*var_name;
	char	*value;

	start = *i;
	(*i)++;
	if (!str[start + 1] || (!ft_isalnum(str[start + 1])
		&& str[start + 1] != '_'))
		return (ft_strdup("$", data));
	start++;
	while (str[start] && (ft_isalnum(str[start]) || str[start] == '_'))
		start++;
	var_name = ft_substr(data, str, *i, start - *i);
	value = expand_env_var(data, var_name);
	*i = start;
	return (value);
}

char	*handle_export_var(t_data *data, char *str, int *i)
{
	int		start;
	char	*var_name;
	char	*value;

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