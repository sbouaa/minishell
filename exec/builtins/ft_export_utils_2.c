/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:12:56 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 20:20:49 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	swap_env(t_env *a, t_env *b)
{
	char	*tmp_key;
	char	*tmp_val;

	tmp_key = a->key;
	tmp_val = a->value;
	a->key = b->key;
	a->value = b->value;
	b->key = tmp_key;
	b->value = tmp_val;
}

t_env	*ft_sort_env(t_env *env)
{
	t_env	*sorted;
	t_env	*ptr;
	t_env	*next;

	sorted = copy_env(env);
	if (!sorted)
		return (NULL);
	ptr = sorted;
	while (ptr)
	{
		next = ptr->next;
		while (next)
		{
			if (ft_strcmp(ptr->key, next->key) > 0)
				swap_env(ptr, next);
			next = next->next;
		}
		ptr = ptr->next;
	}
	return (sorted);
}

char	*expand_var_value(char *value, t_env *env)
{
	char	*expanded;

	if (!value)
		return (ft_strdup_env(""));
	expanded = expand(value, env, NULL);
	if (!expanded)
		return (ft_strdup_env(""));
	return (expanded);
}
