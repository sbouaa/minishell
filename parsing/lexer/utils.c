/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:26:17 by amsaq             #+#    #+#             */
/*   Updated: 2025/06/26 15:38:40 by sbouaa           ###   ########.fr       */
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


