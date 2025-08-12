/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 06:39:51 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:52:24 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	init_data(t_data *data)
{
	if (!data)
		return (1);
	data->prompt = NULL;
	data->token_list = NULL;
	data->syntax_error = 0;
	data->gc.head = NULL;
	data->exit_status = 0;
	data->commands = NULL;
	data->heredoc_fd = -1;
	data->flag_herdoc = 0;
	return (0);
}
