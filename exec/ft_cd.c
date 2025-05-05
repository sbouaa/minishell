/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:37 by sbouaa            #+#    #+#             */
/*   Updated: 2025/05/05 04:51:54 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	up_pwd_env(char *o_cwd, t_env	*env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		perror("minishell: cd: error retrieving current directory: "
			"getcwd: cannot access parent directories");
	else
		printf("");
	//ft_unset("PWD");
	//ft_export("PWD=cwd");
	//ft_unset("OLDPWD");
	//ft_export("OLDPWD=o_cwd");
	return (0);
}

static int	cd_home(char	*o_cwd, t_env	*env)
{
	char	*home;

	home = ft_getenv("HOME", env);
	if (!home)
		return (ft_putendl_fd("cd : HOME not set", 2), 1);
	if (chdir(home) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		return (perror(home), 1);
	}
	if (!up_pwd_env(o_cwd, env))
		return (1);
	return (0);
}

int	cd(char	*dir, t_dd	*data)
{
	char	*cwd;

	if (ft_getenv("PWD", data->env))
		cwd = ft_strdup(ft_getenv("PWD", data->env));
	else
		cwd = ft_strdup("");
	if (!dir)
		return (cd_home(cwd, data->env));
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		return (perror(dir), 1);
	}
	if (!up_pwd_env(cwd, data->env))
		return (1);
	return (0);
	//to_do : free cwd
}
