/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 04:08:49 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/16 22:39:22 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int n, int *length)
{
	if (n == -2147483648)
		ft_putstr("-2147483648", length);
	else
	{
		if (n < 0)
		{
			ft_putchar('-', length);
			n *= -1;
		}
		if (n >= 10)
			ft_putnbr((n / 10), length);
		ft_putchar((n % 10) + '0', length);
	}
}
