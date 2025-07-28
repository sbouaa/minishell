/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:12:10 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/28 09:05:15 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pipe_errors(t_token *token)
{
	if (token->type == PIPE)
	{
		if (!token->next || token->next->type == PIPE)
		{
			ft_printf("Syntax error: unexpected token `|'\n");
			return (258);
		}
	}
	return (0);
}

int	check_redirection_errors(t_token *token)
{
	if (is_redirection(token))
	{
		if (!token->next || !is_word_token(token->next))
		{
			if (token->type == HEREDOC)
				ft_printf("Syntax error: expected delimiter after `<<'\n");
			else
				ft_printf("Syntax error: expected filename after redirection\n");
			return (258);
		}
	}
	return (0);
}

int	check_heredoc_errors(t_token *token)
{
	if (token->type == HEREDOC)
	{
		if (!token->next || !is_word_token(token->next))
		{
			ft_printf("Syntax error: expected delimiter after `<<'\n");
			return (258);
		}
		if (token->next->value && ft_strlen(token->next->value) == 0)
		{
			ft_printf("Syntax error: empty heredoc delimiter\n");
			return (258);
		}
		if (token->next->value && !is_valid_heredoc_delimiter(token->next->value))
		{
			ft_printf("Syntax error: invalid heredoc delimiter\n");
			return (258);
		}
		if (token->next && token->next->next && token->next->next->type == HEREDOC)
		{
			ft_printf("Syntax error: unexpected token `<<'\n");
			return (258);
		}
	}
	return (0);
}

static int	check_first_token(t_token *cur, t_data *data)
{
	if (cur->type == PIPE)
	{
		ft_printf("Syntax error: unexpected token `|'\n");
		data->exit_status = 258;
		return (1);
	}
	return (0);
}

static int	check_last_token(t_token *cur, t_data *data)
{
	if (cur && cur->type == PIPE)
	{
		ft_printf("Syntax error: unexpected end after `|'\n");
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
		if (check_pipe_errors(cur) || check_redirection_errors(cur) || check_heredoc_errors(cur))
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
