/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 01:17:49 by sbouaa            #+#    #+#             */
/*   Updated: 2025/04/27 06:32:31 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char	**cmd)
{
	int	i;
	int	code;

	if (!cmd[1])
		exit(0);
	i = 0;
	code = ft_atoi(cmd[1]);
	while (cmd[1][i])
	{
		if (!ft_isdigit(cmd[1][i]))
		{
			ft_putstr_fd("exit: ", 2);
			ft_putstr_fd(cmd[1], 2);
			(ft_putendl_fd(": numeric argument required", 2), exit(2));
		}
		i++;
	}
	exit(code);
}
// cd 1/2/4/5 rmove diroctory and update the pwd and join them with /..

int	cd(char	*dir, t_dd	*data)
{
	char	*home;

	if (!dir)
	{
		home = getenv("HOME");
		if (!home)
			return (ft_putendl_fd("cd : HOME not set", 2), 1);
		dir = home;
	}
	if (chdir(dir) == -1)
		return (ft_putstr_fd("cd: ", 2), perror(dir), 1);
	home = getcwd(NULL, 0);
	if (home != NULL)
	{
		free(data->old_pwd);
		data->old_pwd = home;
	}
	return (0);
}
//update the pwd and join them with /..

void	pwd(t_dd	*data)
{
	char	*dir;

	dir = getcwd(NULL, 0);
	if (dir != NULL)
	{
		(ft_putendl_fd(dir, 1), free(data->old_pwd));
		data->old_pwd = dir;
	}
	else if (data->old_pwd != NULL)
		ft_putendl_fd(data->old_pwd, 1);
}
// t_env key value key = value

void	env(char	**env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

void	echo(char *line)
{
	int	i;
	int	nl;
	int	j;

	i = 5;
	nl = 1;
	while (line[i] == ' ')
		i++;
	while (line[i] == '-' && line[i + 1] == 'n')
	{
		j = i + 2;
		while (line[j] == 'n')
			j++;
		if (line[j] == ' ' || line[j] == '\0')
		{
			nl = 0;
			i = j;
			while (line[i] == ' ')
				i++;
		}
		else
			break ;
	}
	ft_putstr_fd(&line[i], 1);
	if (nl)
		write(1, "\n", 1);
}
