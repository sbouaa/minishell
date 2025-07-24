/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:08:50 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/22 08:08:51 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	remove_current_command(t_command **head, t_command **current_cmd)
{
	t_command	*prev;
	t_command	*to_remove;

	if (!*current_cmd)
		return ;
	to_remove = *current_cmd;
	if (*head == *current_cmd)
	{
		*head = (*current_cmd)->next;
		*current_cmd = NULL;
		return ;
	}
	prev = *head;
	while (prev && prev->next != *current_cmd)
		prev = prev->next;
	if (prev)
	{
		prev->next = (*current_cmd)->next;
		*current_cmd = NULL;
	}
}

t_token	*handle_error_and_skip_to_pipe(t_command **head,
	t_command **current_cmd, t_token *current)
{
	remove_current_command(head, current_cmd);
	while (current && current->type != PIPE)
		current = current->next;
	return (current);
}
