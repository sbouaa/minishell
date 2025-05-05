/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:06:42 by sbouaa            #+#    #+#             */
/*   Updated: 2025/05/05 05:12:02 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir != NULL)
	{
		ft_putendl_fd(dir, 1);
		free(dir);
	}
	else
		perror("minishell : ");
}
