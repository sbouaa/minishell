/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:09:14 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/20 16:26:34 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_env	*def_env(void)
{
	t_env	*env;
	char	*pwd;

	env = NULL;
	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		if (!add_env_var("PWD", pwd, &env))
			return (free(pwd), NULL);
		free(pwd);
	}
	add_env_var("PATH", DEF_PATH, &env);
	export_var("SHLVL=1", env);
	export_var("_=/usr/bin/env", env);
	export_var("OLDPWD", env);
	return (env);
}

char	*ft_getenv(char *name, t_env *env)
{
	int	i;

	if (!name || !env)
		return (NULL);
	i = ft_strlen(name);
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static t_env	*env_node(char *envp)
{
	char	*key;
	char	*value;
	char	*del;
	t_env	*node;

	del = ft_strchr(envp, '=');
	if (!del)
		return (NULL);
	key = ft_substr(envp, 0, del - envp);
	value = ft_strdup(del + 1);
	if (!key || !value)
		return (NULL);
	node = ft_lstnew(key, value);
	if (!node)
		return (NULL);
	return (node);
}

t_env	*init_env(char **envp)
{
	int		i;
	t_env	*env;
	t_env	*node;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		node = env_node(envp[i]);
		if (!node)
			return (NULL);
		ft_lstadd_back(&env, node);
		i++;
	}
	return (env);
}

void	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value[0])
			printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
