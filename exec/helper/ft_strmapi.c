/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 07:49:55 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 19:52:31 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

char	*ft_strmapi(char const	*s, char (*f)(unsigned int, char))
{
	char	*p;
	int		i;

	if (!s || !f)
		return (NULL);
	p = g_malloc((ft_strlen(s) + 1) * sizeof(char), MALLOC);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		p[i] = (*f)(i, s[i]);
		i++;
	}
	p[i] = '\0';
	return (p);
}
