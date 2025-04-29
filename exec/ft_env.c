/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:09:14 by sbouaa            #+#    #+#             */
/*   Updated: 2025/04/29 20:08:02 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char	**envp)
{
	t_env	*env;
	t_env	*node;
	char	*key;
	char	*value;
	char	*del;
	int		i;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		del = ft_strchr(envp[i], '=');
		if (del)
		{
			key = ft_substr(envp[i], 0, del - envp[i]);
			value = ft_strdup(del + 1);
			node = mn_lstnew(key, value);
			mn_lstadd_back(&env, node);
		}
		i++;
	}
	return (env);
}

static void	print_env(t_env	*env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}

void	env(t_dd	*data)
{
	print_env(data->env);
}
