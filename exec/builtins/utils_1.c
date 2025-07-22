/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:08:36 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/22 19:32:30 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*init_data_exec(char **envp)
{
	t_env	*env;

	if (!envp[0])
		env = def_env();
	else
		env = init_env(envp);
	return (env);
}

t_env	*ft_search_env(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_env	*add_env_var(char *key, char *value, t_env **env)
{
	t_env	*node;
	t_env	*ex_node;
	char	*new_value;

	//if (!key || !value)
	//	return (NULL);
	if (!value)
	{
		key = ft_strdup_s(key);
		node = ft_lstnew_s(key, value);
		ft_lstadd_back(env, node);
	}
	ex_node = ft_search_env(key, *env);
	if (ex_node)
	{
		new_value = ft_strdup_s(value);
		ex_node->value = new_value;
		return (ex_node);
	}
	key = ft_strdup_s(key);
	value = ft_strdup_s(value);
	node = ft_lstnew_s(key, value);
	ft_lstadd_back(env, node);
	return (node);
}
