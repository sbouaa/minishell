/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:06:42 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/12 17:46:36 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	pwd(t_env	*env)
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
			ft_putendl_fd("minishell: pwd: ", 2);
	}
}
