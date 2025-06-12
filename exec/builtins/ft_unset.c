/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 02:58:12 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/12 17:46:40 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	env_del(char *name, t_env **env)
{
	t_env	*prev;
	t_env	*current;

	if (!name || !env || !*env)
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

	if (!args || !env || !*env)
		return (1);
	i = 0;
	while (args[i])
	{
		env_del(args[i], env);
		i++;
	}
	return (0);
}
