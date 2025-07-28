/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:01:17 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/28 18:01:18 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_redirections(t_redirection *redir)
{
	while (redir)
	{
		ft_printf("  Redirection:\n");
		ft_printf("    Type: %d\n", redir->type);
		ft_printf("    File: %s\n", redir->file);
		ft_printf("    FD: %d\n", redir->fd);
		redir = redir->next;
	}
}

void	print_parsed_commands(t_command *cmd)
{
	int				i;
	t_redirection	*redir;

	while (cmd)
	{
		ft_printf("Command:\n");
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			ft_printf("  Arg[%d]: %s\n", i, cmd->args[i]);
			i++;
		}
		redir = cmd->redirects;
		print_redirections(redir);
		cmd = cmd->next;
	}
}

void	print_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		ft_printf("Token[%d]:\n", i);
		ft_printf("  Type      : %d\n", token->type);
		ft_printf("  Value     : %s\n", token->value);
		ft_printf("  Ambiguous : %d\n", token->ambiguous);
		token = token->next;
		i++;
	}
}

void	set_es_signal(int set, t_data *data)
{
	static t_data	*ptr;

	if (set)
		ptr = data;
	if (ptr)
		ptr->exit_status = 130;
}
