/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:08:36 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/12 17:46:46 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*ft_search_env(char	*key, t_env	*env)
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

	if (!key || !value)
		return (NULL);
	ex_node = ft_search_env(key, *env);
	if (ex_node)
	{
		free(ex_node->value);
		ex_node->value = ft_strdup(value);
		if (!ex_node->value)
			return (NULL);
		return (ex_node);
	}
	key = ft_strdup(key);
	value = ft_strdup(value);
	if (!key || !value)
		return (NULL);
	node = ft_lstnew(key, value);
	if (!node)
		return (NULL);
	ft_lstadd_back(env, node);
	return (node);
}
