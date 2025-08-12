/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:01:17 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:51:07 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_es_signal(int set, t_data *data)
{
	static t_data	*ptr;

	if (set)
		ptr = data;
	if (ptr)
		ptr->exit_status = 1;
}
