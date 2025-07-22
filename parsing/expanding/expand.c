/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:00:00 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/22 06:50:38 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	skip_redirect_spaces(t_expand *exp)
{
	while (exp->str[exp->i] == ' ' || exp->str[exp->i] == '\t')
		process_char(exp);
	while (exp->str[exp->i] && exp->str[exp->i] != ' '
		&& exp->str[exp->i] != '\t')
		process_char(exp);
}

static void	skip_redirect_part(t_expand *exp)
{
	int		r_len;
	char	*redir;

	exp->to_expand = 0;
	r_len = is_redirect(exp->str, exp->i);
	if (r_len == 6)
		exp->to_expand = 1;
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
		expanded = expand(token->value, env, data);
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
		else if (token->type == HEREDOC && token->next)
			token = token->next;
		token = token->next;
	}
}

char	*expand(char *prompt, t_env *env, t_data *data)
{
	t_expand	exp;

	exp.i = 0;
	exp.in_single = 0;
	exp.in_double = 0;
	exp.str = (char *)prompt;
	exp.result = ft_strdup("");
	while (exp.str[exp.i])
	{
		update_quote_states(exp.str[exp.i], &exp.in_single, &exp.in_double);
		if (!exp.in_single && !exp.in_double
			&& is_redirect(exp.str, exp.i))
			skip_redirect_part(&exp);
		else if (exp.str[exp.i] == '$' && !exp.in_single)
			process_dollar(&exp, env, data);
		else
			process_char(&exp);
	}
	return (exp.result);
}
