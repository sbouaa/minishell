/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 02:58:06 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 20:20:58 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	to_env(char *key, char *var, int type, t_env *env)
{
	char	*value;
	char	*expanded;

	if (type == 3)
		return (add_env_var(key, NULL, &env), 0);
	else
	{
		value = get_key_and_value(var, 1);
		if (!value)
			return (1);
		expanded = expand_var_value(value, env);
		add_env_var(key, expanded, &env);
		return (1);
	}
	return (0);
}

int	var_in_env(char *key, char *var, int type, t_env *env)
{
	char	*value;
	char	*n_value;
	char	*expanded;
	t_env	*ex_var;

	if (type == 3)
		return (0);
	value = get_key_and_value(var, type);
	if (!value)
		return (1);
	ex_var = ft_search_env(key, env);
	if (type == 1)
	{
		expanded = expand_var_value(value, env);
		ex_var->value = expanded;
		return (0);
	}
	if (type == 2)
	{
		expanded = expand_var_value(value, env);
		n_value = ft_strjoin_env(ex_var->value, expanded);
		ex_var->value = n_value;
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
		return (1);
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

	if (!env)
		return (1);
	copy = ft_sort_env(env);
	if (!copy)
		return (1);
	while (copy)
	{
		if (ft_strcmp(copy->key, "_") != 0)
		{
			if (!copy->value)
				(ft_putstr_fd("declare -x ", 1), ft_putendl_fd(copy->key, 1));
			else
			{
				(ft_putstr_fd("declare -x ", 1), ft_putstr_fd(copy->key, 1));
				(ft_putstr_fd("=\"", 1), ft_putstr_fd(copy->value, 1));
				ft_putendl_fd("\"", 1);
			}
		}
		copy = copy->next;
	}
	return (0);
}

int	ft_export(char **args, t_env	*env)
{
	int	i;
	int	stat;

	i = 1;
	stat = 0;
	if (!args[1])
		return (ft_export_no_args(env), 0);
	i = 1;
	if (args[1] && ft_strcmp(args[1], "--") == 0)
	{
		if (!args[2])
			return (ft_export_no_args(env), 0);
		i++;
	}
	while (args[i])
	{
		if (export_var(args[i], env) != 0)
		{
			stat = 1;
			pr_error(args[i]);
		}
		i++;
	}
	return (stat);
}
