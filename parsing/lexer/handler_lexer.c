/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:26:08 by amsaq             #+#    #+#             */
/*   Updated: 2025/06/23 23:02:18 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_redirections(t_data *data, char *line, int *i)
{
	if (line[*i] == '>' && line[*i + 1] == '>')
	{
		add_node_to_back(data, APPEND, ">>");
		*i += 2;
	}
	else if (line[*i] == '<' && line[*i + 1] == '<')
	{
		add_node_to_back(data, HEREDOC, "<<");
		*i += 2;
	}
	else if (line[*i] == '>')
	{
		add_node_to_back(data, OUT_REDIRECT, ">");
		(*i)++;
	}
	else if (line[*i] == '<')
	{
		add_node_to_back(data, IN_REDIRECT, "<");
		(*i)++;
	}
}
void	handle_token(t_data *data, char *line, int *i)
{
	if (line[*i] == '|')
	{
		add_node_to_back(data, PIPE, "|");
		(*i)++;
	}
	else
		handle_redirections(data, line, i);
}

int	check_quote_syntax(char *line, int start, int end)
{
	int		i;
	int		in_quote;
	char	current_quote;

	in_quote = 0;
	current_quote = '\0';
	i = start;
	while (i < end)
	{
		if (is_quote(line[i]))
		{
			if (!in_quote)
			{
				in_quote = 1;
				current_quote = line[i];
			}
			else if (line[i] == current_quote)
			{
				in_quote = 0;
				current_quote = '\0';
			}
		}
		i++;
	}
	return (in_quote);
}

int	handle_word(t_data *data, char *line, int *i)
{
	int		start;
	char	current_quote;
	char	*content;

	start = *i;
	current_quote = '\0';
	while (line[*i])
	{
		if (!current_quote && is_quote(line[*i]))
			current_quote = line[*i];
		else if (current_quote && line[*i] == current_quote)
			current_quote = '\0';
		else if (!current_quote && (is_space(line[*i]) || is_token(line[*i])))
			break ;
		(*i)++;
	}
	if (check_quote_syntax(line, start, *i))
	{
		data->syntax_error = 1;
		return (printf("Syntax error: unclosed quote\n"), 1);
	}
	if (start == *i)
		return (0);
	content = ft_substr(line, start, *i - start);
	add_node_to_back(data, WORD, content);
	return (0);
}
