/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 05:32:25 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 19:52:16 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

char	*ft_strjoin_env(char const	*s1, char const	*s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	char	*p;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup_env(s2));
	if (!s2)
		return (ft_strdup_env(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	p = gc_malloc((s1_len + s2_len + 1) * sizeof(char), MALLOC);
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
