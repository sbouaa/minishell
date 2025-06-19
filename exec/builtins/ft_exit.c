/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:02 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/19 20:06:40 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char *nb)
{
	int		i;
	int		code;
	char	*s;

	s = nb;
	ft_putendl_fd("exit", 1);
	if (!nb || !*nb)
		(g_malloc(0, FREE), exit(0));
	i = 0;
	if (nb[i] == '+' || nb[i] == '-')
		i++;
	while (nb[i])
	{
		if (!ft_isdigit(nb[i]))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n", s);
			g_malloc(0, FREE);
			exit(2);
		}
		i++;
	}
	code = ft_atoi(nb);
	g_malloc(0, FREE);
	exit(code);
}
