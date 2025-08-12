/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:02 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/27 06:47:24 by sbouaa           ###   ########.fr       */
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
		(ft_putstr_fd("minishell: exit: ", 2), ft_putstr_fd(s, 2));
		ft_putstr_fd(": numeric argument required\n", 2);
		gc_malloc(0, FREE);
		g_malloc(0, FREE);
		close_all(-2, 1);
		exit(255);
	}
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return ;
	}
	gc_malloc(0, FREE);
	g_malloc(0, FREE);
	close_all(-2, 1);
	exit((unsigned char)code);
}

void	ft_exit(char **args)
{
	char	*s;
	int		i;

	if (isatty(0))
		ft_putendl_fd("exit", 1);
	s = args[1];
	if (!s || !*s)
		(gc_malloc(0, FREE), g_malloc(0, FREE), close_all(-2, 1), exit(0));
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
		{
			(ft_putstr_fd("minishell: exit: ", 2), ft_putstr_fd(s, 2));
			ft_putstr_fd(": numeric argument required\n", 2);
			(gc_malloc(0, FREE), g_malloc(0, FREE), close_all(-2, 1));
			exit(255);
		}
		i++;
	}
	check_code(args);
	return ;
}
