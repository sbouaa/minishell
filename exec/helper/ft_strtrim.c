/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 02:27:35 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 19:52:45 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

static int	ft_init(char c, char const	*set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const	*s1, char const	*set)
{
	char	*p;
	size_t	i;
	size_t	start;
	size_t	end;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_init(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_init(s1[end - 1], set))
		end--;
	p = g_malloc((end - start + 1) * sizeof(char), MALLOC);
	if (!p)
		return (NULL);
	i = 0;
	while (start < end)
		p[i++] = s1[start++];
	p[i] = '\0';
	return (p);
}
