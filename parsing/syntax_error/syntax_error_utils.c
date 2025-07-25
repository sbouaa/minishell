/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:09:39 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/22 08:12:02 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
