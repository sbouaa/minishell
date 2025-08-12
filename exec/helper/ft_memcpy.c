/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 06:40:11 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 19:51:33 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

void	*ft_memcpy(void	*dst, const void	*src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	if (dst == src)
		return (dst);
	i = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}
