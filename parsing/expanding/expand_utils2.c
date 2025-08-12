/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:00:00 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:51:16 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_redirect(char *s, int i)
{
	if ((s[i] == '>' || s[i] == '<') && s[i + 1] == s[i])
		return (2);
	if (s[i] == '>' || s[i] == '<')
		return (1);
	return (0);
}

void	handle_special_dollar(t_expand *exp)
{
	exp->i += 2;
}

void	handle_quote_dollar(t_expand *exp)
{
	exp->i++;
}

void	init_expand(t_expand *exp, char *prompt)
{
	exp->i = 0;
	exp->in_single = 0;
	exp->in_double = 0;
	exp->str = prompt;
	exp->result = ft_strdup("");
	exp->to_expand = 1;
}

void	process_char(t_expand *exp)
{
	char	tmp[2];

	tmp[0] = exp->str[exp->i];
	tmp[1] = '\0';
	exp->result = ft_strjoin(exp->result, tmp);
	exp->i++;
}
