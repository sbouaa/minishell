/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:10:38 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/29 19:33:35 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_pipe(t_pipe *p, t_command *cmd)
{
	p->cmd_size = ft_cmd_size(cmd);
	p->pids = g_malloc(sizeof(pid_t) * p->cmd_size, MALLOC);
	if (!p->pids)
		return (1);
	p->prev_fd = -1;
	p->i = 0;
	return (0);
}

int	wait_for_all_processes(pid_t *pids, int count)
{
	int	i;
	int	status;
	int	last_status;

	i = 0;
	last_status = 0;
	status = 0;
	while (i < count)
	{
		waitpid(pids[i], &status, 0);
		if (i == count - 1)
		{
			if (WIFEXITED(status))
				last_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				last_status = 128 + WTERMSIG(status);
		}
		i++;
	}
	return (last_status);
}

void	execute_child_process(t_command *cmd, int prev_fd, int *fd, t_env **env)
{
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, 0) == -1)
			(perror("dup2"), exit(1));
		close(prev_fd);
	}
	if (cmd->next)
	{
		close(fd[0]);
		if (dup2(fd[1], 1) == -1)
			(perror("dup2"), exit(1));
		close(fd[1]);
	}
	execute_child_cmd(cmd, env);
}

int	wait_and_get_status(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int	exec_cmd(char *path, char **env, t_command *cmd)
{
	pid_t	pid;

	dont_display(1, 1);
	if (ft_strnstr(path, "minishell"))
		signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd->args, env);
		exit(check_file(cmd->args[0]));
	}
	if (pid > 0)
		return (wait_and_get_status(pid));
	return (0);
}
