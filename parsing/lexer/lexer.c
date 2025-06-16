/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:26:11 by amsaq             #+#    #+#             */
/*   Updated: 2025/06/16 21:34:45 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	lexer(t_data *data)
{
	int i;
	char *line;
//	int had_space;

	if (!data || !data->prompt)
		return (1);
	i = 0;
	line = data->prompt;
	data->token_list = NULL;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (is_token(line[i]))
			handle_token(data, line, &i);
		else if (handle_word(data, line, &i))
			return (1);
	}
	return (0);
}