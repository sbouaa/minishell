/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:54 by sbouaa            #+#    #+#             */
/*   Updated: 2025/04/29 19:06:23 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(char *line)
{
	int	i;
	int	nl;
	int	j;

	i = 5;
	nl = 1;
	while (line[i] == ' ')
		i++;
	while (line[i] == '-' && line[i + 1] == 'n')
	{
		j = i + 2;
		while (line[j] == 'n')
			j++;
		if (line[j] == ' ' || line[j] == '\0')
		{
			nl = 0;
			i = j;
			while (line[i] == ' ')
				i++;
		}
		else
			break ;
	}
	ft_putstr_fd(&line[i], 1);
	if (nl)
		write(1, "\n", 1);
}
