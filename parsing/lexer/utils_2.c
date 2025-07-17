/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/03 15:26:14 by amsaq             #+#    #+#             */
/*   Updated: 2025/06/17 17:52:24 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_token(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r');
}

int	is_quote(int c)
{
	return (c == '\'' || c == '\"');
}

int	skip_spaces(char *line, int *i)
{
	while (line[*i] && is_space(line[*i]))
		(*i)++;
	return (0);
}

char	*get_token_type_string(t_token_type type)
{
	 char	*type_strings[] = {"PIPE", "IN_REDIRECT", "OUT_REDIRECT",
			"HEREDOC", "APPEND", "WORD"};

	if (type >= 0)
		return (type_strings[type]);
	return ("UNKNOWN");
}

void	print_token_list(t_data *data)
{
	t_token *current;
	int i;

	if (!data || !data->token_list)
	{
		printf("No tokens to display\n");
		return ;
	}

	i = 0;
	current = data->token_list;
	printf("\nToken List:\n");
	printf("----------------------------------------\n");
	while (current)
	{
		printf("Token %d:\n", i++);
		printf("  Type: %s\n", get_token_type_string(current->type));
		printf("  Value: |%s|\n", current->value ? current->value : "NULL");
		printf("  Ambiguos %d:\n", current->ambiguous);
		printf("----------------------------------------\n");
		current = current->next;
	}
}