/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 02:58:12 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/26 15:40:32 by sbouaa           ###   ########.fr       */
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

int	ft_unset(char **args, t_env **env)
{
	int		i;

	if (!args || !*args[0])
		return (1);
	i = 1;
	while (args[i])
	{
		if (ft_strcmp(args[i], "_") != 0)
			env_del(args[i], env);
		i++;
	}
	return (0);
}
