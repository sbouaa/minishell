/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 20:04:32 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 19:50:43 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helper.h"

long long	ft_atoi_s(char	*str)
{
	int		i;
	long	res;
	long	store;
	int		signe;

	i = 0;
	res = 0;
	store = 0;
	signe = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		store = res;
		res = res * 10 + (str[i++] - '0');
		if (store != (res / 10))
			return (MAX_L);
	}
	return (res * signe);
}
