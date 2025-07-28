/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 07:46:22 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/28 18:13:44 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_export_var(char *str)
{
	if (!ft_strncmp(str, "export ", 7))
	{
		str += 7;
		while (*str && *str != '=')
			str++;
		if (!*str)
			return (0);
		str++;
		return (*str == '$');
	}
	return (0);
}

void	expand_loop(t_expand *exp, t_env *env, t_data *data, int is_export, int flag_herdoc)
{
	while (exp->str[exp->i])
	{
		update_quote_states(exp->str[exp->i], &exp->in_single, &exp->in_double);
		if (!exp->in_single && !exp->in_double && is_redirect(exp->str, exp->i))
			skip_redirect_part(exp);
		else if (exp->str[exp->i] == '$' && (!exp->in_single || flag_herdoc))
		{
			if (is_export)
				handle_export_dollar(exp, env, data);
			else
				process_dollar(exp, env, data);
		}
		else
			process_char(exp);
	}
}

char	*expand(char *prompt, t_env *env, t_data *data, int flag_herdoc)
{
	t_expand	exp;
	int			is_export;

	exp.i = 0;
	exp.in_single = 0;
	exp.in_double = 0;
	exp.str = (char *)prompt;
	exp.result = ft_strdup("");
	is_export = is_export_var(prompt);
	expand_loop(&exp, env, data, is_export, flag_herdoc);
	return (exp.result);
}
