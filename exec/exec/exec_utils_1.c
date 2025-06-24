/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:51:22 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/24 20:13:49 by sbouaa           ###   ########.fr       */
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
	while (tmp && ++size)
		tmp = tmp->next;
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

int	check_file(char	*name)
{
    int	fd;

    if (ft_strchr(name, '/'))
    {
        fd = open(name, __O_DIRECTORY);
        if (fd != -1)
        {
            ft_printf("minishell: %s: Is a directory\n", name);
            return (close(fd), 126);
        }
        if (access(name, F_OK) != 0)
            return (ft_printf("minishell: %s: No such file or directory\n", name), 127);
        if (access(name, X_OK) != 0)
            return (ft_printf("minishell: %s: Permission denied\n", name), 126);
    }
    else
        return (ft_printf("minishell: %s: command not found\n", name), 127);
    return (0);
}
