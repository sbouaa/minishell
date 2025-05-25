#include "../minishell.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

char	*ft_strdup(const char *s1, t_data *data)
{
	size_t	i;
	char	*copy;

	i = 0;
	if (!s1 || !data)
		return (NULL);
	copy = (char *)gc_malloc(&data->gc, ft_strlen(s1) + 1);
	if (!copy)
		return (NULL);
	while (s1[i])
	{
		copy[i] = s1[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

char	*ft_strjoin(const char *s1, const char *s2, t_data *data)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2, data));
	if (!s2)
		return (ft_strdup(s1, data));
	str = gc_malloc(&data->gc, ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

t_token	*create_token(t_data *data, t_token_type type, const char *value)
{
	t_token	*token;

	token = (t_token *)gc_malloc(&data->gc, sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
		token->value = ft_strdup(value, data);
	else
		token->value = NULL;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	add_node_to_back(t_data *data, t_token_type type, const char *value)
{
	t_token	*new_token;
	t_token	*current;

	new_token = create_token(data, type, value);
	if (!new_token)
		return ;
	if (data->token_list == NULL)
	{
		data->token_list = new_token;
		new_token->prev = NULL;
		return ;
	}
	current = data->token_list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

char	*ft_substr(t_data *data, const char *s, int start, int len)
{
	char	*str;
	int		i;
	int		s_len;

	if (!s || !data)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup("", data));
	if (len > s_len - start)
		len = s_len - start;
	str = gc_malloc(&data->gc, len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}