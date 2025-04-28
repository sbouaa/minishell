/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 01:41:44 by sbouaa            #+#    #+#             */
/*   Updated: 2025/04/27 06:23:15 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_clean(char	**p)
{
	int	i;

	i = 0;
	while (p[i])
		(free(p[i]), i++);
	free(p);
	p = NULL;
	return ;
}

int	is_builtins(t_dd	*data, char	**envp)
{
	if (!ft_strncmp(data->mmd[0], "echo", 4))
		return (echo(data->line), 0);
	else if (!ft_strncmp(data->mmd[0], "env", 3))
		return (env(envp), 0);
	else if (!ft_strncmp(data->mmd[0], "pwd", 3))
		return (pwd(data), 0);
	else if (!ft_strncmp(data->mmd[0], "cd", 2))
		return (cd(data->mmd[1], data), 0);
	else if (!ft_strncmp(data->mmd[0], "exit", 4))
		return (ft_exit(data->mmd), 0);
	return (1);
}

int main(int ac, char	**av, char	**env)
{
	(void)ac;
	(void)av;
	t_dd *data = malloc(sizeof(t_dd));
	data->mmd = NULL;
	data->line = NULL;
	data->old_pwd = getcwd(NULL, 0);
	char	s[1000];
	while (1)
	{
		printf("\033[1;34m(%s)\033[0m", getcwd(s, 1000));
		data->line = readline("\033[1;32m minishell > \033[0m");
		data->mmd = ft_split(data->line, 32);
		is_builtins(data, env);
		ft_clean(data->mmd);
	}
	return (0);
}