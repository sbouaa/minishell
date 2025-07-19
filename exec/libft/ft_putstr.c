/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 02:39:34 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/16 22:39:31 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr(char	*s, int *length)
{
	if (s == NULL)
	{
		ft_putstr("(null)", length);
		return ;
	}
	while (*s)
	{
		ft_putchar(*s, length);
		s++;
	}
}
