/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:01:23 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:51:04 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_prompt(t_data *data)
{
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
}

int	handle_empty_line(char *line)
{
	if (line)
		free(line);
	return (2);
}

int	handle_lexer_error(t_data *data)
{
	data->token_list = NULL;
	free_prompt(data);
	return (1);
}

int	dont_display(int set, int value)
{
	static int	v;

	if (set)
		v = value;
	return (v);
}

void	setup_interactive_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
