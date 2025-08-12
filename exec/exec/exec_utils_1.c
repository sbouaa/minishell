/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:51:22 by sbouaa            #+#    #+#             */
/*   Updated: 2025/07/27 15:04:18 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_cmd_size(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		cmd = cmd->next;
		i++;
	}
	return (i);
}

char	**switch_env_arr(t_env *env)
{
	int		size;
	char	**arr;
	t_env	*tmp;
	char	*tmp_str;

	size = 0;
	tmp = env;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	arr = g_malloc(sizeof(char *) * (size + 1), MALLOC);
	size = 0;
	tmp = env;
	while (tmp)
	{
		tmp_str = ft_strjoin(tmp->key, "=");
		arr[size++] = ft_strjoin(tmp_str, tmp->value);
		tmp = tmp->next;
	}
	arr[size] = NULL;
	return (arr);
}

char	*ft_find_path(char *cmd, t_env **env)
{
	int		i;
	char	*all_path;
	char	**path;
	t_env	*part;
	char	*tmp;

	i = 0;
	part = ft_search_env("PATH", *env);
	if (!part || !part->value)
	{
		all_path = ft_strjoin("./", cmd);
		if (access(all_path, X_OK | F_OK) == 0)
			return (all_path);
		return (NULL);
	}
	path = ft_split(part->value, ':');
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		all_path = ft_strjoin(tmp, cmd);
		if (access(all_path, X_OK | F_OK) == 0)
			return (all_path);
		i++;
	}
	return (NULL);
}

char	*get_path(char *cmd, t_env **env)
{
	char	*path;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK | F_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path = ft_find_path(cmd, env);
	return (path);
}

int	check_file(char *name)
{
	struct stat	fs;

	if (ft_strchr(name, '/'))
	{
		if (stat(name, &fs) == 0 && S_ISDIR(fs.st_mode))
		{
			(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(name, 2));
			return (ft_putstr_fd(": Is a directory\n", 2), 126);
		}
		if (access(name, F_OK) != 0)
		{
			(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(name, 2));
			return (ft_putstr_fd(": No such file or directory\n", 2), 127);
		}
		if (access(name, X_OK) != 0)
		{
			(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(name, 2));
			return (ft_putstr_fd(": Permission denied\n", 2), 126);
		}
	}
	(ft_putstr_fd("minishell: ", 2), ft_putstr_fd(name, 2));
	return (ft_putstr_fd(": command not found\n", 2), 127);
}
