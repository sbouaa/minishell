/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 02:58:06 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/19 16:46:41 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	to_env(char *key, char *var, int type, t_env *env)
{
	char	*value;

	if (type == 3)
		return (add_env_var(key, "", &env), 0);
	else
	{
		value = get_key_and_value(var, 1);
		if (!value)
			return (1);
		else
			return (add_env_var(key, value, &env), 1);
	}
	return (0);
}

int	var_in_env(char *key, char *var, int type, t_env *env)
{
	char	*value;
	char	*n_value;
	t_env	*ex_var;

	if (type == 3)
		return (0);
	value = get_key_and_value(var, type);
	if (!value)
		return (1);
	ex_var = ft_search_env(key, env);
	if (type == 1)
	{
		ex_var->value = value;
		return (0);
	}
	if (type == 2)
	{
		n_value = ft_strjoin(ex_var->value, value);
		if (!n_value)
			return (1);
		ex_var->value = n_value;
		return (0);
	}
	return (0);
}

int	export_var(char *var, t_env *env)
{
	int		type;
	char	*key;
	t_env	*ex_env;

	key = get_key_and_value(var, 0);
	if (!key)
		return (1);
	if (is_valid(key))
		return (pr_error(var), 1);
	type = get_type(var);
	ex_env = ft_search_env(key, env);
	if (ex_env)
		var_in_env(key, var, type, env);
	else
		to_env(key, var, type, env);
	return (0);
}

int	ft_export_no_args(t_env *env)
{
	t_env	*copy;

	copy = copy_env(env);
	ft_sort_env(copy);
	while (copy)
	{
		if (ft_strcmp(copy->key, "_") != 0)
		{
			if (!copy->value[0])
				printf("declare -x %s\n", copy->key);
			else
				printf("declare -x %s=\"%s\"\n", copy->key, copy->value);
		}
		copy = copy->next;
	}
	return (0);
}

int	ft_export(char **args, t_env	*env)
{
	int	i;

	i = 1;
	if (!args[1] || !*args[1])
		return (ft_export_no_args(env), 0);
	while (args[i])
	{
		if (export_var(args[i], env) != 0)
			return (1);
		i++;
	}
	return (0);
}
