/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:23:01 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 19:51:28 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

void	*ft_memchr(const void	*s, int c, size_t n)
{
	size_t			i;
	unsigned char	oc;
	unsigned char	*ss;

	i = 0;
	ss = (unsigned char *)s;
	oc = (unsigned char )c;
	while (i < n)
	{
		if (ss[i] == oc)
			return ((void *)(ss + i));
		i++;
	}
	return (NULL);
}
