/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 17:42:37 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/20 10:44:23 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/////////////////////////***************************/ this function is from chat \\\\\\\******************** ////////////////////////////

int	setup_redirections(t_command *cmd)
{
	t_redirection	*redir;

	if (!cmd)
		return (1);
	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == IN_REDIRECT)
		{
			cmd->fd_in = open(redir->file, O_RDONLY);
			if (cmd->fd_in < 0)
				return (perror(redir->file), 1);
			if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
				return (perror("dup2"), close(cmd->fd_in), 1);
			close(cmd->fd_in);
		}
		else if (redir->type == OUT_REDIRECT)
		{
			cmd->fd_out = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (cmd->fd_out < 0)
				return (perror(redir->file), 1);
			if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
				return (perror("dup2"), close(cmd->fd_out), 1);
			close(cmd->fd_out);
		}
		else if (redir->type == APPEND)
		{
			cmd->fd_out = open(redir->file, O_WRONLY | O_CREAT | O_APPEND,
					0644);
			if (cmd->fd_out < 0)
				return (perror(redir->file), 1);
			if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
				return (perror("dup2"), close(cmd->fd_out), 1);
			close(cmd->fd_out);
		}
		redir = redir->next;
	}
	return (0);
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
		return (cd(cmd->args[1], *env));
	else if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_exit(cmd->args[1]), 0);
	else if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_unset(cmd->args, env), 0);
	else if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_export(cmd->args, *env));
	return (1);
}

int	handle_child(t_command *cmd, t_pipe *p, t_env **env)
{
	if (cmd->next && pipe(p->fd) == -1)
		return (perror("pipe"), 1);
	p->pids[p->i] = fork();
	if (p->pids[p->i] == -1)
		return (perror("fork"), 1);
	if (p->pids[p->i] == 0)
		execute_child_process(cmd, p->prev_fd, p->fd, env);
	return (0);
}
