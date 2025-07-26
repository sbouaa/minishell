/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:00:00 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/26 10:11:10 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*handle_var_expansion(char *str, int *i, t_env *env)
{
	char	*var;
	char	*value;
	int		start;

	if (!str[*i + 1] || (!ft_isalnum(str[*i + 1]) && str[*i + 1] != '_'))
		return (NULL);
	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	value = ft_getenv(var, env);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

void	process_dollar(t_expand *exp, t_env *env, t_data *data)
{
	if (exp->str[exp->i + 1] == '$')
	{
		exp->i += 2;
		return ;
	}
	if (exp->str[exp->i + 1] == '?')
	{
		handle_exit_status(exp, data);
		return ;
	}
	if (exp->str[exp->i + 1] && (exp->str[exp->i + 1] == '\''
			|| exp->str[exp->i + 1] == '"') && !exp->in_double)
	{
		exp->i++;
		return ;
	}
	exp->expand = handle_var_expansion(exp->str, &exp->i, env);
	if (exp->expand)
	{
		exp->result = ft_strjoin(exp->result, exp->expand);
		return ;
	}
	process_char(exp);
}

void	handle_exit_status(t_expand *exp, t_data *data)
{
	char	*exit_status;

	exit_status = ft_itoa(data->exit_status);
	exp->result = ft_strjoin(exp->result, exit_status);
	exp->i += 2;
}

void	expand_loop(t_expand *exp, t_env *env, t_data *data, int is_export)
{
	while (exp->str[exp->i])
	{
		update_quote_states(exp->str[exp->i], &exp->in_single, &exp->in_double);
		if (!exp->in_single && !exp->in_double && is_redirect(exp->str, exp->i))
			skip_redirect_part(exp);
		else if (exp->str[exp->i] == '$' && !exp->in_single)
		{
			if (is_export)
				process_char(exp);
			else
				process_dollar(exp, env, data);
		}
		else
			process_char(exp);
	}
}

char	*expand(char *prompt, t_env *env, t_data *data)
{
	t_expand	exp;
	int			is_export;

	exp.i = 0;
	exp.in_single = 0;
	exp.in_double = 0;
	exp.str = (char *)prompt;
	exp.result = ft_strdup("");
	is_export = is_export_var(prompt);
	expand_loop(&exp, env, data, is_export);
	return (exp.result);
}
