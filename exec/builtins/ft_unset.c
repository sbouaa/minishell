/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 02:58:12 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/27 14:30:03 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	env_del(char *name, t_env **env)
{
	t_env	*prev;
	t_env	*current;

	if (!name)
		return (1);
	prev = NULL;
	current = *env;
	while (current)
	{
		if (ft_strcmp(current->key, name) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			return (0);
		}
		prev = current;
		current = current->next;
	}
	return (1);
}

int	is_valid_2(char *key)
{
	int	i;

	i = 0;
	if (!key || !key[0] || key[0] == ' ')
		return (pr_error(key), 1);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (pr_error(key), 1);
		i++;
	}
	return (0);
}

int	ft_unset(char **args, t_env **env)
{
	int		i;
	int		stat;

	if (!args || !*args[0])
		return (1);
	i = 1;
	stat = 0;
	while (args[i])
	{
		if (ft_strcmp(args[i], "_") != 0)
		{
			if (is_valid_2(args[i]) != 0)
				stat = 1;
			env_del(args[i], env);
		}
		i++;
	}
	return (stat);
}
