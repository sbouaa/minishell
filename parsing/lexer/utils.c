/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:26:14 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:51:45 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_token(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	is_quote(int c)
{
	return (c == '\'' || c == '\"');
}

int	skip_spaces(char *line, int *i)
{
	while (line[*i] && is_space(line[*i]))
		(*i)++;
	return (0);
}

char	*get_token_type_string(t_token_type type)
{
	char	*type_strings[6];

	type_strings[0] = "PIPE";
	type_strings[1] = "IN_REDIRECT";
	type_strings[2] = "OUT_REDIRECT";
	type_strings[3] = "HEREDOC";
	type_strings[4] = "APPEND";
	type_strings[5] = "WORD";
	if (type >= 0 && type < 6)
		return (type_strings[type]);
	return ("UNKNOWN");
}
