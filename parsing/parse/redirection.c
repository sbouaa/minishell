/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:09:25 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:52:09 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	add_redirection_to_list(t_command *cmd, t_redirection *new_redir)
{
	t_redirection	*last_redir;

	if (!cmd->redirects)
		cmd->redirects = new_redir;
	else
	{
		last_redir = cmd->redirects;
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = new_redir;
	}
}

static t_redirection	*create_redirection(t_data *data, t_token *current)
{
	t_redirection	*new_redir;

	new_redir = g_malloc(sizeof(t_redirection), MALLOC);
	if (!new_redir)
		return (NULL);
	ft_bzero(new_redir, sizeof(t_redirection));
	new_redir->type = current->type;
	new_redir->file = ft_strdup(current->next->value);
	if (new_redir->type == HEREDOC)
	{
		if (handle_heredoc(data, new_redir) != 0)
			return (NULL);
	}
	return (new_redir);
}

static int	check_redirection_syntax(t_token *current, t_data *data)
{
	if (!current || !current->next)
	{
		ft_putstr_fd("minishell: syntax error `newline'\n", 2);
		data->exit_status = 258;
		return (1);
	}
	if (current->next->ambiguous)
	{
		ft_putstr_fd("minishell: ambiguous redirect\n", 2);
		data->exit_status = 1;
		return (1);
	}
	return (0);
}

int	parse_redirection(t_data *data, t_command *cmd, t_token *current)
{
	t_redirection	*new_redir;

	if (!cmd)
		return (0);
	if (check_redirection_syntax(current, data))
		return (1);
	new_redir = create_redirection(data, current);
	if (!new_redir)
		return (1);
	add_redirection_to_list(cmd, new_redir);
	return (0);
}
