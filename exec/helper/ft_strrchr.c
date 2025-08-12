/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:00:37 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 20:06:21 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

char	*ft_strrchr(const char	*s, int c)
{
	char	ch;
	size_t	len;

	ch = (char )c;
	len = ft_strlen(s);
	while (len > 0)
	{
		if (*(s + len) == ch)
			return ((char *)(s + len));
		len--;
	}
	if (*s == ch)
		return ((char *)s);
	return (NULL);
}
