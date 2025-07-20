/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 16:58:57 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/27 09:42:59 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup_s(const char	*s1)
{
	int		i;
	char	*p;

	if (!s1)
		return (NULL);
	p = gc_malloc(ft_strlen(s1) + 1, MALLOC);
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	p[i] = '\0';
	return (p);
}
