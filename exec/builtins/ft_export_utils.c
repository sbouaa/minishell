/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:35:41 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/12 17:46:24 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	is_valid(char *key)
{
	int	i;

	i = 0;
	if (!key || ft_isdigit(key[0]))
		return (1);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

char	*get_key_and_value(char *var, int type)
{
	char	*pos;

	if (type)
	{
		pos = ft_strchr(var, '=');
		if (!pos)
			return (NULL);
		return (ft_strdup(pos + 1));
	}
	else
	{
		pos = ft_strchr(var, '=');
		if (!pos)
			return (ft_strdup(var));
		if (pos && *(pos - 1) == '+')
			pos--;
		return (ft_substr(var, 0, pos - var));
	}
}

int	get_type(char *var)
{
	char	*p;

	p = ft_strchr(var, '=');
	if (!p)
		return (3);
	if (*(p - 1) == '+')
		return (2);
	return (1);
}

void	pr_error(char *var)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(": not a valid identifier\n", 2);
}