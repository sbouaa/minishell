/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:26:17 by amsaq             #+#    #+#             */
/*   Updated: 2025/06/16 21:36:05 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*token;

	token = g_malloc(sizeof(t_token), MALLOC);
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
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

	new_token = create_token(type, value);
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

char	*ft_substr_m(t_data *data, const char *s, int start, int len)
{
	char	*str;
	int		i;
	int		s_len;

	if (!s || !data)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	str = g_malloc(len + 1, MALLOC);
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
/*
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}*/
