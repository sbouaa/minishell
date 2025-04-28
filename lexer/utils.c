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
char	*ft_substr(t_data *data, const char *s, int start, int len)
{
	char	*substr;
	int		i;
	int		slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if ((size_t)start >= (size_t)slen)
	{
		substr = gc_malloc(&data->gc, 1);
		if (!substr)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if ((size_t)(start + len) > (size_t)slen)
		len = slen - start;
	substr = gc_malloc(&data->gc, len + 1);
	if (!substr)
		return (NULL);
	i = -1;
	while (++i < len)
		substr[i] = s[start + i];
	substr[i] = '\0';
	return (substr);
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
		data->token_list = new_token;
	else
	{
		current = data->token_list;
		while (current->next != NULL)
			current = current->next;
		current->next = new_token;
	}
}

char *get_token_type_string(t_token_type type)
{
    if (type == PIPE)
        return ("PIPE");
    else if (type == IN_REDIRECT)
        return ("IN_REDIRECT");
    else if (type == OUT_REDIRECT)
        return ("OUT_REDIRECT");
    else if (type == HEREDOC)
        return ("HEREDOC");
    else if (type == APPEND)
        return ("APPEND");
    else if (type == QUOTE)
        return ("QUOTE");
    else if (type == WORD)
        return ("WORD");
    else
        return ("UNKNOWN");
}

void print_tokens(t_data *data)
{
    t_token *current;

    current = data->token_list;
    while (current)
    {
        printf("Token type: %s | value: %s\n",
               get_token_type_string(current->type),
               current->value ? current->value : "NULL");
        current = current->next;
    }
}
