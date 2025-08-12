/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:09:39 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:52:17 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pipe_errors(t_token *token)
{
	if (token->type == PIPE)
	{
		if (!token->next || token->next->type == PIPE)
		{
			ft_putstr_fd("Syntax error: unexpected token `|'\n", 2);
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
				ft_putstr_fd("Syntax error: expected del `<<'\n", 2);
			else
				ft_putstr_fd("Syntax error: expected filename after rdr\n", 2);
			return (258);
		}
	}
	return (0);
}

int	is_redirection(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == IN_REDIRECT || token->type == OUT_REDIRECT
		|| token->type == HEREDOC || token->type == APPEND);
}

int	is_word_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == WORD);
}

int	is_valid_heredoc_delimiter(char *delimiter)
{
	if (!delimiter)
		return (0);
	while (*delimiter)
	{
		if (*delimiter == '<' || *delimiter == '>' || *delimiter == '|')
			return (0);
		delimiter++;
	}
	return (1);
}
