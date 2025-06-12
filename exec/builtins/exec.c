/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 01:41:44 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/12 23:29:20 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_dd	*init_datas(t_dd	*data, char	**envp)
{
	data = g_malloc(sizeof(t_dd), MALLOC);
	if (!data)
		return (NULL);
	data->exit_status = 0;
	if (!envp[0])
		data->env = def_env();
	else
		data->env = init_env(envp);
	return (data);
}

int	is_builtins(t_dd	*data)
{
	if (ft_strcmp(data->mmd[0], "echo") == 0)
		return (echo(data->line), data->exit_status);
	else if (ft_strcmp(data->mmd[0], "env") == 0)
		return (env(data->env), data->exit_status);
	else if (ft_strcmp(data->mmd[0], "pwd") == 0)
		return (pwd(data->env), data->exit_status);
	else if (ft_strcmp(data->mmd[0], "cd") == 0)
		return (cd(data->mmd[1], data), data->exit_status);
	else if (ft_strcmp(data->mmd[0], "exit") == 0)
		return (ft_exit(data->mmd[1]), data->exit_status);
	else if (ft_strcmp(data->mmd[0], "unset") == 0)
		return (ft_unset(data->mmd, &data->env));
	else if (ft_strcmp(data->mmd[0], "export") == 0)
		return (ft_export(data->mmd, data), data->exit_status);
	else
		return (ft_putstr_fd("minishell : Syntax Error\n", 2), 1);
}
/*
int	main(int ac, char	**av, char	**env)
{
	t_dd	*data;

	(void)ac;
	(void)av;
	data = NULL;
	data = init_datas(data, env);
	while (1)
	{
		data->line = readline("\033[1;32m minishell > \033[0m");
		if (!*data->line)
		{
			printf("%s", data->line);
			continue ;
		}
		add_history(data->line);
		data->mmd = ft_split(data->line, 32);
		is_builtins(data);
	}
	return (0);
}*/
