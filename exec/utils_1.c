/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:08:36 by sbouaa            #+#    #+#             */
/*   Updated: 2025/05/05 06:24:18 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env   *add_env_var(char *key, char *value, t_env **env)
{
    t_env   *node;

    key = ft_strdup(key);
    value = ft_strdup(value);
    if (!key || !value)
        return (ft_clear(env), NULL);
    node = ft_lstnew(value, key);
    if (!node)
        return (ft_clear(env), NULL);
    ft_lstadd_back(env, node);
    return node;
}

