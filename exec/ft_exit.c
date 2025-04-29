/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:02 by sbouaa            #+#    #+#             */
/*   Updated: 2025/04/29 19:05:25 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char	**cmd)
{
	int	i;
	int	code;

	if (!cmd[1])
		exit(0);
	i = 0;
	code = ft_atoi(cmd[1]);
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			(ft_putendl_fd(": numeric argument required", 2), exit(2));
		}
		i++;
	}
	exit(code);
}