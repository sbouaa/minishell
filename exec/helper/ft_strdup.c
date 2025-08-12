/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 00:48:27 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 19:52:10 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

char	*ft_strdup(const char	*s1)
{
	int		i;
	char	*p;

	if (!s1)
		return (NULL);
	p = g_malloc(ft_strlen(s1) + 1, MALLOC);
	i = -1;
	while (s1[++i])
		p[i] = s1[i];
	p[i] = '\0';
	return (p);
}
