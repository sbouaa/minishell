/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:54 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/16 17:51:41 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_echo_args(char **args, int i)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	echo(char **args)
{
	int	i;
	int	nl;
	int	j;

	i = 1;
	nl = 1;
	while (args[i] && args[i][0] == '-' && args[i][1] == 'n')
	{
		j = 2;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] == '\0')
		{
			nl = 0;
			i++;
		}
		else
			break ;
	}
	print_echo_args(args, i);
	if (nl)
		write(1, "\n", 1);
}
