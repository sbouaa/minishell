/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 19:05:37 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/28 17:43:48 by sbouaa           ###   ########.fr       */
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
		n_pwd = ft_strjoin(temp, dir);
	}
	if (ft_getkey("pwd", *env))
		add_env_var("OLDPWD", o_cwd, env);
	if (ft_getkey("OLDPWD", *env))
		add_env_var("PWD", n_pwd, env);
	return (0);
}

static int	up_pwd_env(char *o_cwd, char *dir, t_env **env)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (getcwd_fail(o_cwd, dir, env));
	if (ft_getkey("OLDPWD", *env))
	{
		if (o_cwd && *o_cwd)
			add_env_var("OLDPWD", o_cwd, env);
		else
			env_del("OLDPWD", env);
	}
	if (ft_getkey("PWD", *env))
		add_env_var("PWD", cwd, env);
	return (free(cwd), 0);
}

static int	cd_home(char *o_cwd, t_env **env)
{
	char	*home;

	home = ft_getenv("HOME", *env);
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(home) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		return (perror(home), 1);
	}
	if (up_pwd_env(o_cwd, NULL, env) != 0)
		return (1);
	return (0);
}

static int	cd_exec(char **args, t_env **env, char *cwd, int nf)
{
	int	ret;

	if (!args[1])
		ret = cd_home(cwd, env);
	else if (chdir(args[1]) == -1)
	{
		if (!*args[1])
			return (0);
		ft_putstr_fd("minishell: cd: ", 2);
		ret = (perror(args[1]), 1);
	}
	else if (up_pwd_env(cwd, args[1], env) != 0)
		ret = 1;
	else
		ret = 0;
	if (nf)
		free(cwd);
	return (ret);
}

int	cd(char **args, t_env **env)
{
	char	*cwd;
	int		nf;

	nf = 0;
	cwd = getcwd(NULL, 0);
	if (cwd)
		nf = 1;
	else
		cwd = ft_strdup(ft_getenv("PWD", *env));
	if (!cwd)
		cwd = ft_strdup("");
	return (cd_exec(args, env, cwd, nf));
}
