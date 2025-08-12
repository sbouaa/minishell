/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:06:42 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/27 14:44:54 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pwd(t_env	*env)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir)
	{
		ft_putendl_fd(dir, 1);
		free(dir);
	}
	else
	{
		dir = ft_getenv("PWD", env);
		if (dir)
			ft_putendl_fd(dir, 1);
		else
		{
			ft_putstr_fd("minishell: pwd: ", 2);
			ft_putstr_fd("error retrieving current directory\n", 2);
			return (1);
		}
	}
	return (0);
}
