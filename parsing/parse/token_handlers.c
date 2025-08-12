/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:09:20 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:52:12 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	init_command_args(t_data *data, t_command *cmd, char *value)
{
	char	**args;

	(void)data;
	if (!cmd || value == NULL)
		return ;
	args = g_malloc(sizeof(char *) * 2, MALLOC);
	if (!args)
		return ;
	args[0] = ft_strdup(value);
	args[1] = NULL;
	cmd->args = args;
}

int	handle_word_token(t_parse_context *ctx, t_token *current)
{
	if (current->ambiguous)
	{
		ft_putstr_fd("minishell: : ambiguous redirect\n", 2);
		ctx->data->exit_status = 1;
		return (1);
	}
	if (!*(ctx->current_cmd))
	{
		*(ctx->current_cmd) = parse_command(ctx->data, ctx->head,
				*(ctx->current_cmd));
		if (*(ctx->current_cmd) && current->value != NULL)
			init_command_args(ctx->data, *(ctx->current_cmd),
				current->value);
	}
	else
		add_argument(ctx->data, *(ctx->current_cmd), current->value);
	return (0);
}

int	handle_redirection_token(t_parse_context *ctx, t_token *current)
{
	if (!*(ctx->current_cmd))
		*(ctx->current_cmd) = parse_command(ctx->data, ctx->head,
				*(ctx->current_cmd));
	if (*(ctx->current_cmd))
		return (parse_redirection(ctx->data, *(ctx->current_cmd), current));
	return (0);
}

int	is_redirection_token(int type)
{
	return (type == IN_REDIRECT || type == OUT_REDIRECT
		|| type == APPEND || type == HEREDOC);
}

t_token	*handle_redirection_parsing(t_parse_context *ctx, t_token *current)
{
	*(ctx->error_flag) = handle_redirection_token(ctx, current);
	if (current->next && current->next->next)
		return (current->next->next);
	return (NULL);
}
