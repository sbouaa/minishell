/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:08:36 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/24 18:23:31 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_dd	*init_data_exec(t_dd *data, char **envp)
{
	data = gc_malloc(sizeof(t_dd), MALLOC);
	if (!data)
		return (NULL);
	if (!envp[0])
		data->env = def_env();
	else
		data->env = init_env(envp);
	return (data);
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

	if (!key || !value)
		return (NULL);
	ex_node = ft_search_env(key, *env);
	if (ex_node)
	{
		new_value = ft_strdup_s(value);
		if (!new_value)
			return (NULL);
		ex_node->value = new_value;
		return (ex_node);
	}
	key = ft_strdup_s(key);
	value = ft_strdup_s(value);
	if (!key || !value)
		return (NULL);
	node = ft_lstnew_s(key, value);
	if (!node)
		return (NULL);
	ft_lstadd_back(env, node);
	return (node);
}
