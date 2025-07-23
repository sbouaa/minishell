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

static int	handle_error_and_cleanup(t_data *data)
{
	data->syntax_error = 1;
	data->exit_status = 258;
	ft_printf("Syntax error: unclosed quote\n");
	return (1);
}

static int	is_export_command(t_data *data)
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
	int		start;
	char	current_quote;
	char	*content;
	int		is_export;
	int		has_dollar;

	start = *i;
	current_quote = '\0';
	is_export = is_export_command(data);
	has_dollar = (line[*i] == '$');

	while (line[*i])
	{
		if (!current_quote && is_quote(line[*i]))
			current_quote = line[*i];
		else if (current_quote && line[*i] == current_quote)
			current_quote = '\0';
		else if (!current_quote && (is_space(line[*i]) || is_token(line[*i])))
		{
			if (is_export && has_dollar)
			{
				// For export with $var, keep going until space or =
				if (line[*i] != ' ' && line[*i] != '=')
					continue;
			}
			break;
		}
		(*i)++;
	}
	if (check_quote_syntax(line, start, *i))
		return (handle_error_and_cleanup(data));
	if (start == *i)
		return (0);
	content = ft_substr(line, start, *i - start);
	add_node_to_back(data, WORD, content);
	return (0);
}
