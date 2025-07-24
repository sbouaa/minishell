/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 01:48:50 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/25 16:12:47 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	shell_do(char *arg, char **env)
{
	char	*sh[3];

	sh[0] = "/bin/sh";
	sh[1] = arg;
	sh[2] = NULL;
	execve("/bin/sh", sh, env);
	exit(check_file(arg));
}
