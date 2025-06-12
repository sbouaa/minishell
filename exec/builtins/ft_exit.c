/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:02 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/12 17:46:21 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


void	ft_exit(char	*nb)
{
	int	i;
	int	code;

	ft_putendl_fd("exit", 1);
	if (!nb || !*nb)
		exit(0);
	i = 0;
	code = ft_atoi(nb);
	while (nb[i])
	{
		if (!ft_isdigit(nb[i]))
		{
			g_malloc(0, FREE);
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(nb, 2);
			(ft_putendl_fd(": numeric argument required", 2), exit(2));
		}
		i++;
	}
	g_malloc(0, FREE);
	exit(code);
}
