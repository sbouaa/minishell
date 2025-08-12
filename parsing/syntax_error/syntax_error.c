/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:12:10 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:52:20 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_heredoc_errors(t_token *token)
{
	if (token->type == HEREDOC)
	{
		if (!token->next || !token->next->value[0]
			|| !is_word_token(token->next))
			return (ft_putstr_fd("Syntax error: expected `<<'\n", 2), 258);
		if (token->next->value
			&& !is_valid_heredoc_delimiter(token->next->value))
			return (ft_putstr_fd("Syntax error: invalid heredoc dl\n", 2), 258);
	}
	return (0);
}

static int	check_first_token(t_token *cur, t_data *data)
{
	if (cur->type == PIPE)
	{
		ft_putstr_fd("Syntax error: unexpected token `|'\n", 2);
		data->exit_status = 258;
		return (1);
	}
	return (0);
}

static int	check_last_token(t_token *cur, t_data *data)
{
	if (cur && cur->type == PIPE)
	{
		ft_putstr_fd("Syntax error: unexpected end after `|'\n", 2);
		data->exit_status = 258;
		return (1);
	}
	return (0);
}

int	check_syntax_errors(t_data *data)
{
	t_token	*cur;

	cur = data->token_list;
	if (!cur)
		return (0);
	if (check_first_token(cur, data))
		return (1);
	while (cur)
	{
		if (check_pipe_errors(cur) || check_redirection_errors(cur)
			|| check_heredoc_errors(cur))
		{
			data->exit_status = 258;
			return (1);
		}
		cur = cur->next;
	}
	cur = data->token_list;
	while (cur && cur->next)
		cur = cur->next;
	if (check_last_token(cur, data))
		return (1);
	return (0);
}
