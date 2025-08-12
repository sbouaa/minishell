/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amsaq <amsaq@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 18:01:11 by amsaq             #+#    #+#             */
/*   Updated: 2025/07/29 20:51:00 by amsaq            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

static int	process_expansion(t_data *data, t_env *env)
{
	char	*old_prompt;

	old_prompt = data->prompt;
	data->prompt = expand(data->prompt, env, data);
	free(old_prompt);
	if (lexer(data))
		return (handle_lexer_error(data));
	return (0);
}

int	handle_prompt(t_data *data, t_env *env)
{
	char	*line;

	line = readline("minishell > ");
	if (!line)
	{
		write(1, "exit\n", 5);
		return (33);
	}
	if (line[0] == '\0')
		return (handle_empty_line(line));
	data->prompt = line;
	add_history(data->prompt);
	if (lexer(data))
		return (handle_lexer_error(data));
	if (check_syntax_errors(data))
		return (handle_lexer_error(data));
	if (process_expansion(data, env))
		return (1);
	expand_redirections(data->token_list, data->env, data);
	return (0);
}

void	execute_commands(t_data *data)
{
	t_command	*commands;

	commands = parse_tokens(data);
	if (commands)
		data->exit_status = ft_begin_exec(commands, &data->env);
}

void	sigint_handler(int sig)
{
	(void)sig;
	g_signal = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	set_es_signal(0, NULL);
	rl_replace_line("", 0);
	if (!dont_display(0, 0))
		rl_redisplay();
	else
		dont_display(1, 0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		status;

	(void)ac;
	(void)av;
	set_es_signal(1, &data);
	if (init_data(&data) != 0)
		return (1);
	data.env = init_data_exec(env);
	while (1)
	{
		dont_display(1, 0);
		setup_interactive_signals();
		status = handle_prompt(&data, data.env);
		if (status == 1 || status == 2)
			continue ;
		if (status == 33)
			break ;
		data.token_list = quote_remove(&data);
		execute_commands(&data);
		close_all(-2, 1);
	}
	(close_all(-2, 1), g_malloc(0, FREE));
	return (gc_malloc(0, FREE), data.exit_status);
}
