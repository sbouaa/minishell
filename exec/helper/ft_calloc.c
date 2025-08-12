/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 00:10:44 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 19:50:53 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (size && count && count > 18446744073709551615ULL / size)
		return (NULL);
	p = g_malloc(count * size, MALLOC);
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, count * size);
	return (p);
}
