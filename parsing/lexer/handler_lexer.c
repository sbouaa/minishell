/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_lexer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 06:29:37 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/22 08:18:52 by amsaq            ###   ########.fr       */
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
		handle_heredoc_word(data, line, i);
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

int	is_export_command(t_data *data)
{
	t_token	*last;

	last = data->token_list;
	if (!last)
		return (0);
	while (last->next)
		last = last->next;
	return (last && ft_strcmp(last->value, "export") == 0);
}

int	handle_word(t_data *data, char *line, int *i)
{
	int			start;
	char		current_quote;
	t_word_info	info;

	start = *i;
	current_quote = '\0';
	info.is_export = is_export_command(data);
	info.has_dollar = (line[*i] == '$');
	while (line[*i])
	{
		if (process_word_char(line, i, &current_quote, &info))
			break ;
		(*i)++;
	}
	if (check_quote_syntax(line, start, *i))
		return (handle_error_and_cleanup(data));
	if (start == *i)
		return (0);
	add_node_to_back(data, WORD, ft_substr(line, start, *i - start));
	return (0);
}
