/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_lexer_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 06:29:37 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:51:32 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	process_word_char(char *line, int *i, char *current_quote,
	t_word_info *info)
{
	if (!*current_quote && is_quote(line[*i]))
		*current_quote = line[*i];
	else if (*current_quote && line[*i] == *current_quote)
		*current_quote = '\0';
	else if (!*current_quote && (is_space(line[*i]) || is_token(line[*i])))
	{
		if (info->is_export && info->has_dollar)
		{
			if (line[*i] != ' ' && line[*i] != '=')
				return (0);
		}
		return (1);
	}
	return (0);
}

int	handle_heredoc_word(t_data *data, char *line, int *i)
{
	int		start;
	char	current_quote;
	char	*content;
	t_token	*token;

	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
	start = *i;
	current_quote = '\0';
	while (line[*i])
	{
		if (!current_quote && (line[*i] == '\'' || line[*i] == '\"'))
			current_quote = line[*i];
		else if (current_quote && line[*i] == current_quote)
			current_quote = '\0';
		else if (!current_quote && (is_space(line[*i]) || is_token(line[*i])))
			break ;
		(*i)++;
	}
	content = ft_substr(line, start, *i - start);
	token = add_node_to_back(data, WORD, content);
	if (token)
		token->quoted = (ft_strchr(content, '\'') || ft_strchr(content, '\"'));
	return (0);
}

int	handle_error_and_cleanup(t_data *data)
{
	data->syntax_error = 1;
	data->exit_status = 258;
	ft_putstr_fd("Syntax error: unclosed quote\n", 2);
	return (1);
}
