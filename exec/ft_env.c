/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:09:14 by sbouaa            #+#    #+#             */
/*   Updated: 2025/05/05 02:48:52 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char	*name, t_env	*env)
{
	int	i;

	i = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(env->key, name, i) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

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
			node = ft_lstnew(key, value);
			ft_lstadd_back(&env, node);
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
