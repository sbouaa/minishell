/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:37 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/19 21:05:57 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	getcwd_fail(char *o_cwd, char *dir, t_env **env)
{
	char	*n_pwd;
	char	*temp;
	int		len;

	perror("minishell: cd: error retrieving current directory: "
		"getcwd: cannot access parent directories");
	len = ft_strlen(o_cwd);
	if (len > 0 && o_cwd[len - 1] == '/')
		n_pwd = ft_strjoin(o_cwd, dir);
	else
	{
		temp = ft_strjoin(o_cwd, "/");
		if (!temp)
			return (1);
		n_pwd = ft_strjoin(temp, dir);
	}
	if (!n_pwd)
		return (1);
	add_env_var("OLDPWD", o_cwd, env);
	add_env_var("PWD", n_pwd, env);
	return (0);
}

static int	up_pwd_env(char *o_cwd, char *dir, t_env **env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (getcwd_fail(o_cwd, dir, env));
	if (o_cwd && *o_cwd)
		add_env_var("OLDPWD", o_cwd, env);
	else
		env_del("OLDPWD", env);
	if (ft_getenv("PWD", *env))
		add_env_var("PWD", cwd, env);
	return (free(cwd), 0);
}

static int	cd_home(char *o_cwd, t_env *env)
{
	char	*home;

	home = ft_getenv("HOME", env);
	if (!home)
		return (ft_printf("minishell: cd: HOME not set\n"), 1);
	if (chdir(home) == -1)
	{
		ft_printf("minishell: cd: ");
		return (perror(home), 1);
	}
	if (!up_pwd_env(o_cwd, NULL, &env))
		return (1);
	return (0);
}

int	cd(char *dir, t_env *env)
{
	char	*cwd;

	if (ft_getenv("PWD", env))
		cwd = ft_strdup(ft_getenv("PWD", env));
	else
		cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("");
	if (!dir)
		return (cd_home(cwd, env));
	if (chdir(dir) == -1)
	{
		ft_printf("minishell: cd: ");
		return (perror(dir), free(cwd), 1);
	}
	if (up_pwd_env(cwd, dir, &env) == 1)
		return (free(cwd), 1);
	free(cwd);
	return (0);
}
