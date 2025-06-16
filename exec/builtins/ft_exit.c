/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:02 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/16 22:50:14 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char	*nb)
{
	int	i;
	int	code;

	ft_putendl_fd("exit", 1);
	if (!nb || !*nb)
		(g_malloc(0, FREE), exit(0));
	i = 0;
	code = ft_atoi(nb);
	while (nb[i])
	{
		if (!ft_isdigit(nb[i]))
		{
			g_malloc(0, FREE);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(nb, 2);
			(ft_printf(": numeric argument required\n"), exit(2));
		}
		i++;
	}
	g_malloc(0, FREE);
	exit(code);
}
