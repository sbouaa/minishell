/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:07:39 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/22 08:07:40 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*quote_append_substr(t_data *data, char *res,
		t_quote_ctx *ctx, char *str)
{
	int		len;
	char	*sub;
	char	*temp;

	(void)data;
	len = ctx->i - ctx->start;
	sub = ft_substr(str, ctx->start, len);
	temp = ft_strjoin(res, sub);
	return (temp);
}

static char	*quote_append_char(t_data *data, char *res, char c)
{
	char	tmp[2];
	char	*temp;

	(void)data;
	tmp[0] = c;
	tmp[1] = '\0';
	temp = ft_strjoin(res, tmp);
	return (temp);
}

static void	quote_handle(t_data *data, char *str, t_quote_ctx *ctx)
{
	if (!ctx->in_single && !ctx->in_double)
	{
		ctx->start = ctx->i + 1;
		ctx->was_quoted = 1;
	}
	else
	{
		ctx->result = quote_append_substr(data, ctx->result, ctx, str);
		ctx->was_quoted = 0;
	}
	if (str[ctx->i] == '\'' && !ctx->in_double)
		ctx->in_single = !ctx->in_single;
	else if (str[ctx->i] == '"' && !ctx->in_single)
		ctx->in_double = !ctx->in_double;
}

static char	*quote_remove_single(t_data *data, char *str)
{
	t_quote_ctx	ctx;

	ctx.i = 0;
	ctx.in_single = 0;
	ctx.in_double = 0;
	ctx.start = 0;
	ctx.was_quoted = 0;
	ctx.result = ft_strdup("");
	while (str && str[ctx.i])
	{
		if ((str[ctx.i] == '\'' && !ctx.in_double)
			|| (str[ctx.i] == '"' && !ctx.in_single))
			quote_handle(data, str, &ctx);
		else if (!ctx.in_single && !ctx.in_double && !ctx.was_quoted)
			ctx.result = quote_append_char(data, ctx.result, str[ctx.i]);
		ctx.i++;
	}
	if (ctx.in_single || ctx.in_double)
		ctx.result = quote_append_substr(data, ctx.result, &ctx, str);
	return (ctx.result);
}

t_token	*quote_remove(t_data *data)
{
	t_token	*current;

	current = data->token_list;
	while (current)
	{
		if (current->value)
			current->value = quote_remove_single(data, current->value);
		current = current->next;
	}
	return (data->token_list);
}
