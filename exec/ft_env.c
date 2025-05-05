/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:09:14 by sbouaa            #+#    #+#             */
/*   Updated: 2025/05/05 06:22:02 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    if (!add_env_var("SHLVL", "1", &env))
        return (NULL);
    if (!add_env_var("_", "/usr/bin/env", &env))
        return (NULL);
    return (env);
}

char	*ft_getenv(char *name, t_env *env)
{
	int	i;

	i = ft_strlen(name);
	while (env)
	{
		if (ft_strncmp(env->key, name, i) == 0)
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
		return (free(key), free(value), NULL);
	node = ft_lstnew(key, value);
	if (!node)
		(free(key), free(value));
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
			return (ft_clear(&env), NULL);
		ft_lstadd_back(&env, node);
		i++;
	}
	return (env);
}

void	env(t_env *env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
