/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:00:00 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/22 06:51:07 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	process_char(t_expand *exp)
{
	char	tmp[2];

	tmp[0] = exp->str[exp->i];
	tmp[1] = '\0';
	exp->result = ft_strjoin(exp->result, tmp);
	exp->i++;
}

char	*handle_var_expansion(char *str, int *i, t_env *env)
{
	char	*var;
	char	*value;
	int		start;
	int		is_cmd;

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
	is_cmd = (str[0] == '$' && !ft_strchr(str, '='));
	if (is_cmd)
		return (ft_strdup(value)); 
	return (ft_strdup(value));
}

int	is_redirect(char *s, int i)
{
	if ((s[i] == '>' || s[i] == '<') && s[i + 1] == s[i])
		return (2);
	if (s[i] == '>' || s[i] == '<')
		return (1);
	return (0);
}

void	process_dollar(t_expand *exp, t_env *env, t_data *data)
{
	char	*exit_status;
	char	*expanded;
	int		is_cmd;

	if (exp->str[exp->i + 1] == '$')
	{
		exp->i += 2;
		return ;
	}
	if (exp->str[exp->i + 1] == '?')
	{
		exit_status = ft_itoa(data->exit_status);
		exp->result = ft_strjoin(exp->result, exit_status);
		exp->i += 2;
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
		is_cmd = (exp->str[0] == '$' && !ft_strchr(exp->str, '='));
		if (is_cmd)
		{
			exp->result = ft_strjoin(exp->result, exp->expand);
		}
		else
		{
			expanded = ft_strjoin("$", exp->str + exp->i - ft_strlen(exp->expand));
			exp->result = ft_strjoin(exp->result, expanded);
		}
		return ;
	}
	process_char(exp);
}
