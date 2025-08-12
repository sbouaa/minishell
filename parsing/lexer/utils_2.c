/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:30:22 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:51:42 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*create_token(t_token_type type, const char *value)
{
	t_token	*token;

	token = g_malloc(sizeof(t_token), MALLOC);
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	token->next = NULL;
	token->prev = NULL;
	token->ambiguous = false;
	token->quoted = false;
	return (token);
}

t_token	*add_node_to_back(t_data *data, t_token_type type, const char *value)
{
	t_token	*new_token;
	t_token	*current;

	new_token = create_token(type, value);
	if (!new_token)
		return (NULL);
	if (data->token_list == NULL)
	{
		data->token_list = new_token;
		new_token->prev = NULL;
		return (new_token);
	}
	current = data->token_list;
	while (current->next != NULL)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
	return (new_token);
}
