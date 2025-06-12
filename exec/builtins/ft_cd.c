/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:37 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/12 16:31:45 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	getcwd_fail(char *o_cwd, char *dir, t_env **env)
{
	char	*n_pwd;
	char	*temp;

	perror("minishell: cd: error retrieving current directory: "
		"getcwd: cannot access parent directories");
	if (o_cwd[ft_strlen(o_cwd) - 1] == '/')
		n_pwd = ft_strjoin(o_cwd, dir);
	else
	{
		temp = ft_strjoin(o_cwd, "/");
		if (!temp)
			return (1);
		n_pwd = ft_strjoin(temp, dir);
		free(temp);
	}
	if (!n_pwd)
		return (1);
	add_env_var("OLD_PWD", o_cwd, env);
	add_env_var("PWD", n_pwd, env);
	return (free(n_pwd), 0);
}

static int	up_pwd_env(char *o_cwd, char *dir, t_env **env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (getcwd_fail(o_cwd, dir, env));
	if (o_cwd && *o_cwd)
		add_env_var("OLD_PWD", o_cwd, env);
	else
		env_del("OLD_PWD", env);
	if (ft_getenv("PWD", *env))
		add_env_var("PWD", cwd, env);
	return (free(cwd), 0);
}

static int	cd_home(char *o_cwd, t_env *env)
{
	char	*home;

	home = ft_getenv("HOME", env);
	if (!home)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	if (chdir(home) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		return (perror(home), 1);
	}
	if (!up_pwd_env(o_cwd, NULL, &env))
		return (1);
	return (0);
}

int	cd(char *dir, t_dd *data)
{
	char	*cwd;

	if (ft_getenv("PWD", data->env))
		cwd = ft_strdup(ft_getenv("PWD", data->env));
	else
		cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_strdup("");
	if (!dir)
		return (cd_home(cwd, data->env));
	if (chdir(dir) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		return (perror(dir), free(cwd), 1);
	}
	if (up_pwd_env(cwd, dir, &data->env) == 1)
		return (free(cwd), 1);
	free(cwd);
	return (0);
}
