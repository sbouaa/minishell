/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:02 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/22 20:14:44 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_code(char **args)
{
	long long	code;
	char		*s;

	s = args[1];
	code = ft_atoi_s(s);
	if (code == MAX_L || code == -MAX_L)
	{
		ft_printf("minishell: exit: %s: numeric argument required\n", s);
		gc_malloc(0, FREE);
		exit(2);
	}
	if (args[2])
	{
		ft_printf("minishell: exit: too many arguments\n");
		return ;
	}
	gc_malloc(0, FREE);
	exit((unsigned char)code);
}

void	ft_exit(char **args)
{
	char	*s;
	int		i;

	ft_putendl_fd("exit", 1);
	s = args[1];
	if (!s || !*s)
		(gc_malloc(0, FREE), exit(0));
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
		{
			ft_printf("minishell: exit: %s: numeric argument required\n", s);
			gc_malloc(0, FREE);
			exit(2);
		}
		i++;
	}
	check_code(args);
	return ;
}
