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

t_env *add_env_var(const char *key, const char *value, t_env **env)
{
    t_env *node = ft_lstnew(ft_strdup(key), ft_strdup(value));
    if (!node)
    {
        ft_lstclear(env);
        return NULL;
    }
    ft_lstadd_back(env, node);
    return node;
}

