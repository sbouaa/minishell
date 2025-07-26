#include "minishell.h"

static void	free_prompt(t_data *data)
{
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
}

static void	print_redirections(t_redirection *redir)
{
	while (redir)
	{
		ft_printf("  Redirection:\n");
		ft_printf("    Type: %d\n", redir->type);
		ft_printf("    File: %s\n", redir->file);
		ft_printf("    FD: %d\n", redir->fd);
		redir = redir->next;
	}
}

void	print_parsed_commands(t_command *cmd)
{
	int				i;
	t_redirection	*redir;

	while (cmd)
	{
		ft_printf("Command:\n");
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			ft_printf("  Arg[%d]: %s\n", i, cmd->args[i]);
			i++;
		}
		redir = cmd->redirects;
		print_redirections(redir);
		cmd = cmd->next;
	}
}

void	print_tokens(t_token *token)
{
	int	i;

	i = 0;
	while (token)
	{
		ft_printf("Token[%d]:\n", i);
		ft_printf("  Type      : %d\n", token->type);
		ft_printf("  Value     : %s\n", token->value);
		ft_printf("  Ambiguous : %d\n", token->ambiguous);
		token = token->next;
		i++;
	}
}

static int	handle_empty_line(char *line)
{
	if (line)
		free(line);
	return (2);
}

static int	handle_lexer_error(t_data *data)
{
	data->token_list = NULL;
	free_prompt(data);
	return (1);
}

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
		return (33);
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

void	set_e_status(int set, int status, t_data *data)
{
	static t_data	*ptr;

	if (set)
		ptr = data;
	ptr->exit_status = status;
}

void	signal_handle(int sig)
{
	if (sig == SIGQUIT)
		return ;
	ft_putstr_fd("\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
	set_e_status(0, 130, NULL);
	(void)sig;
}

int	main(int ac, char **av, char **env)
{
	t_data	data;
	int		status;

	(void)ac;
	(void)av;
	if (!isatty(0))
		return (1);
	set_e_status(1, 0, &data);
	signal(SIGINT, &signal_handle);
	signal(SIGQUIT, &signal_handle);
	if (init_data(&data) != 0)
		return (1);
	data.env = init_data_exec(env);
	while (1)
	{
		status = handle_prompt(&data, data.env);
		if (status == 1 || status == 2)
			continue ;
		if (status == 33)
			break ;
		data.token_list = quote_remove(&data);
		execute_commands(&data);
		close_all(-2,1);
		g_malloc(0, FREE);
	}
	gc_malloc(0, FREE);
	return (data.exit_status);
}
