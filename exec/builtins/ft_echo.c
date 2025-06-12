/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:54 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/12 17:46:10 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo(char *line)
{
	int	nl;
	int	j;
	int	i;

	i = ft_strnstr(line, "echo", ft_strlen(line)) - line + 4;
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
