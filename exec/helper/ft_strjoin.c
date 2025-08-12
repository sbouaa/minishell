/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 02:14:23 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 19:52:20 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

char	*ft_strjoin(char const	*s1, char const	*s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*p;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	p = g_malloc((s1_len + s2_len + 1) * sizeof(char), MALLOC);
	ft_memcpy(p, s1, s1_len);
	i = 0;
	while (s2[i] != '\0')
	{
		p[s1_len + i] = s2[i];
		i++;
	}
	p[s1_len + s2_len] = '\0';
	return (p);
}
