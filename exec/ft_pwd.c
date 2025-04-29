/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:06:42 by sbouaa            #+#    #+#             */
/*   Updated: 2025/04/29 19:07:20 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(t_dd	*data)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir != NULL)
	{
		(ft_putendl_fd(dir, 1), free(data->old_pwd));
		data->old_pwd = dir;
	}
	else if (data->old_pwd != NULL)
		ft_putendl_fd(data->old_pwd, 1);
}
