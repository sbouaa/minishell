/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 08:08:21 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/22 08:08:22 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static size_t	count_arguments(char **args)
{
	size_t	count;

	count = 0;
	if (args)
	{
		while (args[count])
			count++;
	}
	return (count);
}

static void	copy_arguments(char **new_args, char **old_args, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		new_args[i] = old_args[i];
		i++;
	}
}

void	add_argument(t_data *data, t_command *cmd, char *value)
{
	size_t	arg_count;
	char	**new_args;

	(void)data;
	if (!cmd || value == NULL)
		return ;
	arg_count = count_arguments(cmd->args);
	new_args = g_malloc(sizeof(char *) * (arg_count + 2), MALLOC);
	if (!new_args)
		return ;
	if (arg_count > 0)
		copy_arguments(new_args, cmd->args, arg_count);
	new_args[arg_count] = ft_strdup(value);
	new_args[arg_count + 1] = NULL;
	cmd->args = new_args;
}
