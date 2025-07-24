/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:11:40 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/16 22:39:02 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void static	ft_check_conversions(const char	*format, va_list args, int *length)
{
	if (*format == '%')
		ft_putchar(*format, length);
	else if (*format == 'd' || *format == 'i')
		ft_putnbr(va_arg(args, int), length);
	else if (*format == 'c')
		ft_putchar((char)va_arg(args, int), length);
	else if (*format == 's')
		ft_putstr(va_arg(args, char *), length);
	else
		ft_putchar(*format, length);
}

int	ft_printf(const char	*format, ...)
{
	va_list	args;
	int		length;

	va_start(args, format);
	length = 0;
	while (*format)
	{
		if (*format == '%' && *(format + 1) == '\0')
			break ;
		if (*format == '%')
		{
			format++;
			ft_check_conversions(format, args, &length);
		}
		else
			ft_putchar(*format, &length);
		format++;
	}
	va_end(args);
	return (length);
}
