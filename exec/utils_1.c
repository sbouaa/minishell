/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:08:36 by sbouaa            #+#    #+#             */
/*   Updated: 2025/05/07 03:02:52 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*add_env_var(char *key, char *value, t_env **env)
{
	t_env	*node;

	if (!key || !value)
		return (ft_putendl_fd("error lah w3lam!!!!!!!", 2), NULL);
	key = ft_strdup(key);
	value = ft_strdup(value);
	if (!key || !value)
		return (ft_clear(env), NULL);
	node = ft_lstnew(key, value);
	if (!node)
		return (ft_clear(env), NULL);
	ft_lstadd_back(env, node);
	return (node);
}
