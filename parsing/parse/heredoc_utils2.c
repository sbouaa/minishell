/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:09:19 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/28 19:09:55 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*create_heredoc_filename(void)
{
	static int	heredoc_count = 0;
	char		*number;
	char		*filename;

	number = ft_itoa(heredoc_count++);
	if (!number)
		return (NULL);
	filename = ft_strjoin("/tmp/.heredoc_", number);
	return (filename);
}

t_token	*find_delimiter_token(t_data *data, char *delimiter)
{
	t_token	*token;

	token = data->token_list;
	while (token)
	{
		if (token->type == HEREDOC && token->next
			&& ft_strcmp(token->next->value, delimiter) == 0)
			return (token->next);
		token = token->next;
	}
	return (NULL);
}
