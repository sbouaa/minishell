/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:35:41 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/16 22:51:02 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*copy_env(t_env *env)
{
	t_env	*new;
	t_env	*last;
	t_env	*curr;
	t_env	*node;

	new = NULL;
	last = NULL;
	curr = env;
	while (curr)
	{
		node = g_malloc(sizeof(t_env), MALLOC);
		if (!node)
			return (NULL);
		node->key = ft_strdup(curr->key);
		node->value = ft_strdup(curr->value);
		node->next = NULL;
		if (!new)
			new = node;
		else
			last->next = node;
		last = node;
		curr = curr->next;
	}
	return (new);
}

int	is_valid(char *key)
{
	int	i;

	i = 0;
	if (!key || ft_isdigit(key[0]))
		return (1);
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

char	*get_key_and_value(char *var, int type)
{
	char	*pos;

	if (type)
	{
		pos = ft_strchr(var, '=');
		if (!pos)
			return (NULL);
		return (ft_strdup(pos + 1));
	}
	else
	{
		pos = ft_strchr(var, '=');
		if (!pos)
			return (ft_strdup(var));
		if (pos && *(pos - 1) == '+')
			pos--;
		return (ft_substr(var, 0, pos - var));
	}
}

int	get_type(char *var)
{
	char	*p;

	p = ft_strchr(var, '=');
	if (!p)
		return (3);
	if (*(p - 1) == '+')
		return (2);
	return (1);
}

void	pr_error(char *var)
{
	ft_printf("minishell: export: %s : not a valid identifier\n", var);
}
