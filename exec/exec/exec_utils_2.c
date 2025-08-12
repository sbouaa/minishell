/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:42:37 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/27 16:14:31 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	close_all(int fd, int flag)
{
	static int	fd_arr[1024];
	static int	count;
	int			i;

	i = 0;
	if (flag == 0)
		fd_arr[count++] = fd;
	else if (flag == 1)
	{
		while (i < count)
			close(fd_arr[i++]);
		count = 0;
	}
}

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_builtin(t_command *cmd, t_env **env)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (echo(cmd->args), 0);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(*env), 0);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (pwd(*env));
	else if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (cd(cmd->args, env));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(cmd->args), 1);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd->args, env));
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(cmd->args, *env));
	return (1);
}

int	handle_child(t_command *cmd, t_pipe *p, t_env **env)
{
	if (cmd->next && pipe(p->fd) == -1)
		return (ft_putstr_fd("minishell: ", 2), perror("pipe"), 1);
	p->pids[p->i] = fork();
	if (p->pids[p->i] == -1)
	{
		while (waitpid(-1, NULL, 0) > 0)
			;
		return (ft_putstr_fd("minishell: ", 2), perror("fork"), 1);
	}
	if (p->pids[p->i] == 0)
		execute_child_process(cmd, p->prev_fd, p->fd, env);
	return (0);
}
