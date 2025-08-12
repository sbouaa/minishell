/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:08:59 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:52:06 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_token	*process_word_token(t_parse_context *ctx, t_token *current)
{
	*(ctx->error_flag) = handle_word_token(ctx, current);
	if (*(ctx->error_flag))
		return (handle_error_and_skip_to_pipe(ctx->head, ctx->current_cmd,
				current));
	return (current->next);
}

static t_token	*process_redirection_token(t_parse_context *ctx,
	t_token *current)
{
	t_token	*next;

	next = handle_redirection_parsing(ctx, current);
	if (*(ctx->error_flag))
		return (handle_error_and_skip_to_pipe(ctx->head, ctx->current_cmd,
				current));
	return (next);
}

static t_token	*process_pipe_token(t_parse_context *ctx, t_token *current)
{
	*(ctx->current_cmd) = parse_pipe(ctx->data, *(ctx->current_cmd));
	return (current->next);
}

static t_token	*process_single_token(t_parse_context *ctx, t_token *current)
{
	if (current->type == WORD)
		return (process_word_token(ctx, current));
	else if (is_redirection_token(current->type))
		return (process_redirection_token(ctx, current));
	else if (current->type == PIPE)
		return (process_pipe_token(ctx, current));
	else
		return (current->next);
}

t_command	*parse_tokens(t_data *data)
{
	t_token			*current;
	t_command		*head;
	t_command		*current_command;
	int				error_flag;
	t_parse_context	ctx;

	head = NULL;
	current_command = NULL;
	current = data->token_list;
	ctx.data = data;
	ctx.current_cmd = &current_command;
	ctx.head = &head;
	ctx.error_flag = &error_flag;
	while (current)
	{
		error_flag = 0;
		current = process_single_token(&ctx, current);
	}
	return (head);
}
