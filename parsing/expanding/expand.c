/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:00:00 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/28 18:15:54 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	skip_redirect_spaces(t_expand *exp)
{
	while (exp->str[exp->i] == ' ' || exp->str[exp->i] == '\t')
		process_char(exp);
	while (exp->str[exp->i] && exp->str[exp->i] != ' '
		&& exp->str[exp->i] != '\t')
		process_char(exp);
}

void	skip_redirect_part(t_expand *exp)
{
	int		r_len;
	char	*redir;

	exp->to_expand = 0;
	r_len = is_redirect(exp->str, exp->i);
	redir = ft_substr(exp->str, exp->i, r_len);
	exp->result = ft_strjoin(exp->result, redir);
	exp->i += r_len;
	skip_redirect_spaces(exp);
}

static void	expand_file_redirect(t_token *token, t_env *env, t_data *data)
{
	char	*expanded;

	if (token->value && ft_strchr(token->value, '$'))
	{
		expanded = expand(token->value, env, data, 0);
		if (!expanded || expanded[0] == '\0' || ft_strchr(expanded, ' '))
			token->ambiguous = true;
		else
			token->value = expanded;
	}
}

void	expand_redirections(t_token *token, t_env *env, t_data *data)
{
	while (token)
	{
		if ((token->type == IN_REDIRECT || token->type == OUT_REDIRECT
				|| token->type == APPEND) && token->next)
		{
			token = token->next;
			expand_file_redirect(token, env, data);
		}
		token = token->next;
	}
}

void	update_quote_states(char c, int *in_s, int *in_d)
{
	if (!*in_s && !*in_d && c == '\'')
		*in_s = 1;
	else if (!*in_s && !*in_d && c == '"')
		*in_d = 1;
	else if (*in_s && c == '\'')
		*in_s = 0;
	else if (*in_d && c == '"')
		*in_d = 0;
}
