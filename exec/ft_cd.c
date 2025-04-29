/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:37 by sbouaa            #+#    #+#             */
/*   Updated: 2025/04/29 19:05:49 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char	*dir, t_dd	*data)
{
	char	*home;

	if (!dir)
	{
		home = getenv("HOME");
		if (!home)
			return (ft_putendl_fd("cd : HOME not set", 2), 1);
		dir = home;
	}
	if (chdir(dir) == -1)
		return (ft_putstr_fd("cd: ", 2), perror(dir), 1);
	home = getcwd(NULL, 0);
	if (home != NULL)
	{
		free(data->old_pwd);
		data->old_pwd = home;
	}
	return (0);
}
