#include "../../minishell.h"

char	*quote_append_substr(t_data *data, char *res,
		char *str, int start, int end)
{
	int		len;
	char	*sub;
	char	*temp;

	len = end - start;
	sub = ft_substr_m(data, str, start, len);
	temp = ft_strjoin(res, sub);
	return (temp);
}

char	*quote_append_char(t_data *data, char *res, char c)
{
	char	tmp[2];
	char	*temp;

	data = 0;
	tmp[0] = c;
	tmp[1] = '\0';
	temp = ft_strjoin(res, tmp);
	return (temp);
}

void	quote_handle(t_data *data, char *str, t_quote_ctx *ctx)
{
	if (!ctx->in_single && !ctx->in_double)
	{
		ctx->start = ctx->i + 1;
		ctx->was_quoted = 1;
	}
	else
	{
		ctx->result = quote_append_substr(data, ctx->result,
				str, ctx->start, ctx->i);
		ctx->was_quoted = 0;
	}
	if (str[ctx->i] == '\'' && !ctx->in_double)
		ctx->in_single = !ctx->in_single;
	else if (str[ctx->i] == '"' && !ctx->in_single)
		ctx->in_double = !ctx->in_double;
}

char	*quote_remove(t_data *data, char *str)
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
		ctx.result = quote_append_substr(data, ctx.result,
				str, ctx.start, ctx.i);
	return (ctx.result);
}
