/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 02:58:06 by sbouaa            #+#    #+#             */
/*   Updated: 2025/05/13 00:30:04 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_export_no_args(t_env *env)
{
    while (env)
    {
        //sort before print
        if (ft_strcmp(env->key, "_") != 0)
            printf("declare -x %s=%s\n", env->key, env->value);
        env = env->next;
    }
    return (0);
}

int ft_export(char  **args, t_dd    *data)
{
    if (!args[1])
        ft_export_no_args(data->env);
    return (0);
}