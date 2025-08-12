/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:32:02 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/27 14:37:57 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_col	*new_node_env(void	*ptr)
{
	t_col	*new;

	new = malloc(sizeof(t_col));
	if (!new)
		return (NULL);
	new->ptr = ptr;
	new->next = NULL;
	return (new);
}

t_col	*last_node_env(t_col **head)
{
	t_col	*tmp;

	if (!head || !*head)
		return (NULL);
	tmp = *head;
	while (tmp != NULL && tmp->next != NULL)
		tmp = tmp->next;
	return (tmp);
}

void	add_back_env(t_col	**head, t_col *new)
{
	if (!head || !new)
		return ;
	if (!*head)
		*head = new;
	else
		last_node_env(head)->next = new;
}

void	clear_all_env(t_col **head)
{
	t_col	*cur;
	t_col	*tmp;

	if (!head || !*head)
		return ;
	cur = *head;
	while (cur)
	{
		tmp = cur->next;
		free(cur->ptr);
		cur->ptr = NULL;
		free(cur);
		cur = tmp;
	}
	*head = NULL;
}

void	*gc_malloc(size_t size, t_call call)
{
	static t_col	*head;
	t_col			*tmp;
	void			*ptr;

	if (call == MALLOC)
	{
		ptr = malloc(size);
		if (!ptr)
			return (clear_all_env(&head), exit(1), NULL);
		tmp = new_node_env(ptr);
		if (!tmp)
			return (clear_all_env(&head), free(ptr), exit(1), NULL);
		add_back_env(&head, tmp);
		return (ptr);
	}
	else if (call == FREE)
		clear_all_env(&head);
	return (NULL);
}
