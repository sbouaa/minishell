#include "../minishell.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0'
			&& c <= '9') || c == '_')
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

char	*join_expanded(t_data *data, char *new_val, char *first, char *exp)
{
	char	*tmp;
	char	*joined;

	if (!new_val)
		return (ft_strjoin(first, exp, data));
	tmp = ft_strjoin(new_val, first, data);
	// free(new_val);
	joined = ft_strjoin(tmp, exp, data);
	// free(tmp);
	return (joined);
}
