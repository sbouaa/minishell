/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:08:37 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/22 08:08:42 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	link_command_to_list(t_command **head, t_command *new_cmd)
{
	t_command	*last_cmd;

	if (!*head)
		*head = new_cmd;
	else
	{
		last_cmd = *head;
		while (last_cmd->next)
			last_cmd = last_cmd->next;
		last_cmd->next = new_cmd;
	}
}

t_command	*parse_command(t_data *data, t_command **head,
	t_command *current_command)
{
	(void)data;
	if (!current_command)
	{
		current_command = g_malloc(sizeof(t_command), MALLOC);
		if (!current_command)
			return (NULL);
		ft_bzero(current_command, sizeof(t_command));
		link_command_to_list(head, current_command);
	}
	return (current_command);
}

t_command	*parse_pipe(t_data *data, t_command *current_command)
{
	(void)data;
	if (!current_command)
		return (NULL);
	if (!current_command->next)
		return (NULL);
	current_command = current_command->next;
	ft_bzero(current_command, sizeof(t_command));
	return (current_command);
}
