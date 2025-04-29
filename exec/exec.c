/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 01:41:44 by sbouaa            #+#    #+#             */
/*   Updated: 2025/04/29 20:12:08 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dd	*init_data(t_dd	*data, char	**envp)
{
	data = malloc(sizeof(t_dd));
	if (!data)
		return (NULL);
	data->old_pwd = getcwd(NULL, 0);
	data->exit_status = 0;
	data->env = init_env(envp);
	return (data);
}

int	is_builtins(t_dd	*data)
{
	if (!ft_strncmp(data->mmd[0], "echo", 4))
		return (echo(data->line), data->exit_status);
	else if (!ft_strncmp(data->mmd[0], "env", 3))
		return (env(data), data->exit_status);
	else if (!ft_strncmp(data->mmd[0], "pwd", 3))
		return (pwd(data), data->exit_status);
	else if (!ft_strncmp(data->mmd[0], "cd", 2))
		return (cd(data->mmd[1], data), data->exit_status);
	else if (!ft_strncmp(data->mmd[0], "exit", 4))
		return (ft_exit(data->mmd), data->exit_status);
	return (1);
}

int	main(int ac, char	**av, char	**env)
{
	t_dd	*data;
	char	s[1000];

	(void)ac;
	(void)av;
	data = NULL;
	data = init_data(data, env);
	while (1)
	{
		printf("\033[1;34m(%s)\033[0m", getcwd(s, 1000));
		data->line = readline("\033[1;32m minishell > \033[0m");
		data->mmd = ft_split(data->line, 32);
		is_builtins(data);
		ft_clean(data->mmd);
	}
	ft_clear(&data->env);
	return (0);
}
