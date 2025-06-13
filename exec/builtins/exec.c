/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 01:41:44 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/13 10:30:41 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_dd	*init_data_exec(t_dd	*data, char	**envp)
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

int	is_builtins(t_command	*data, t_env	*env)
{
	if (ft_strcmp(data->args[0], "echo") == 0)
		return (echo(data->args), 0);
	else if (ft_strcmp(data->args[0], "env") == 0)
		return (ft_env(env), 0);
	else if (ft_strcmp(data->args[0], "pwd") == 0)
		return (pwd(env), 0);
	else if (ft_strcmp(data->args[0], "cd") == 0)
		return (cd(data->args[1], env), 0);
	else if (ft_strcmp(data->args[0], "exit") == 0)
		return (ft_exit(data->args[1]), 0);
	else if (ft_strcmp(data->args[0], "unset") == 0)
		return (ft_unset(data->args, &env), 0);
	else if (ft_strcmp(data->args[0], "export") == 0)
		return (ft_export(data->args, env), 0);
	else
		return (ft_putstr_fd("minishell : Syntax Error\n", 2), 1);
}

int	ft_exec(t_command *camds, t_env	*env)
{
	while (camds)
	{
		is_builtins(camds, env);
		camds = camds->next;
	}
	return (0);
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