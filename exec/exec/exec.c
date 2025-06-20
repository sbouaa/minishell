/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:26:15 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/20 21:39:13 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	execute_child_cmd(t_command *cmd, t_env **env)
{
	char	*path;
	char	**env_arr;

	if (setup_redirections(cmd) != 0)
		exit(1);
	if (is_builtin(cmd->args[0]))
		exit(exec_builtin(cmd, env));
	path = get_path(cmd->args[0], env);
	if (!path)
	{
		ft_printf("minishell: %s: command not found\n", cmd->args[0]);
		exit(127);
	}
	env_arr = switch_env_arr(*env);
	if (!env_arr)
		exit(1);
	//signal(SIGQUIT, SIG_DFL);
	execve(path, cmd->args, env_arr);
	ft_printf("minishell: %s: command not found\n", cmd->args[0]);
	exit(127);
	return (0);
}

int	execute_single(t_command *cmd, t_env **env)
{
	char	*path;
	char	**env_arr;

	if (!cmd || !cmd->args || !*cmd->args[0])
		return (ft_printf("minishell: command not found\n"), 127);
	if (setup_redirections(cmd) != 0)
		return (1);
	if (is_builtin(cmd->args[0]))
		return (exec_builtin(cmd, env));
	path = get_path(cmd->args[0], env);
	if (!path)
	{
		ft_printf("minishell: %s: command not found\n", cmd->args[0]);
		return (127);
	}
	env_arr = switch_env_arr(*env);
	if (!env_arr)
		return (1);
	return (exec_cmd(path, env_arr, cmd));
}

int	multi_pipes(t_command	*cmd, t_env	**env)
{
	t_pipe	p;

	init_pipe(&p, cmd);
	while (cmd)
	{
		if (!cmd || !cmd->args || !*cmd->args[0])
			return (ft_printf("minishell: command not found\n"), 127);
		if (handle_child(cmd, &p, env))
			return (1);
		if (p.prev_fd != -1)
			close(p.prev_fd);
		if (cmd->next)
		{
			close(p.fd[1]);
			p.prev_fd = p.fd[0];
		}
		cmd = cmd->next;
		p.i++;
	}
	return (wait_for_all_processes(p.pids, p.cmd_size));
}

int	ft_exec(t_command *cmd, t_env **env)
{
	if (!cmd)
		return (0);
	if (!cmd->next)
		return (execute_single(cmd, env));
	return (multi_pipes(cmd, env));
}

int	ft_begin_exec(t_command *cmds, t_env *env)
{
	int	in;
	int	out;
	int	exit_status;

	if (!cmds)
		return (0);
	in = dup(0);
	out = dup(1);
	if (in == -1 || out == -1)
		return (perror("dup"), 1);
	exit_status = ft_exec(cmds, &env);
	dup2(in, STDIN_FILENO);
	dup2(out, STDOUT_FILENO);
	close(in);
	close(out);
	return (exit_status);
}
