/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:12:56 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/25 17:37:25 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_sort_env(t_env *env)
{
	t_env	*ptr;
	char	*tmp;

	while (env->next)
	{
		ptr = env;
		while (ptr->next)
		{
			if (ft_strcmp(ptr->key, ptr->next->key) > 0)
			{
				tmp = ptr->key;
				ptr->key = ptr->next->key;
				ptr->next->key = tmp;
				tmp = ptr->value;
				ptr->value = ptr->next->value;
				ptr->next->value = tmp;
			}
			ptr = ptr->next;
		}
		env = env->next;
	}
}
