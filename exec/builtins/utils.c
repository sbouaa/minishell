/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 01:55:25 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/26 15:37:35 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_lstnew_s(char *key, char *value)
{
	t_env	*node;

	node = gc_malloc(sizeof(t_env), MALLOC);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

t_env	*ft_lstnew(char *key, char *value)
{
	t_env	*node;

	node = g_malloc(sizeof(t_env), MALLOC);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	ft_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
