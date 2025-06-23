#include "../../minishell.h"

static void	init_command_args(t_data *data, t_command *cmd, char *value)
{
	char	**args;

	data = 0;
	if (!cmd || !value)
		return ;
	args = g_malloc(sizeof(char *) * 2, MALLOC);
	if (!args)
		return ;
	args[0] = ft_strdup(value);
	args[1] = NULL;
	cmd->args = args;
}

static int	handle_word_token(t_data *data, t_command **current_cmd, t_command **head, t_token *current)
{
	if (current->ambiguous)
	{
		printf("minishell: : ambiguous redirect\n");
		return (1);
	}
	if (!*current_cmd)
	{
		*current_cmd = parse_command(data, head, *current_cmd);
		if (*current_cmd && current->value)
			init_command_args(data, *current_cmd, current->value);
	}
	else
		add_argument(data, *current_cmd, current->value);
	return (0);
}

static int	handle_redirection_token(t_data *data, t_command **current_cmd, t_command **head, t_token *current)
{
	if (!*current_cmd)
		*current_cmd = parse_command(data, head, *current_cmd);
	if (*current_cmd)
		return (parse_redirection(data, *current_cmd, current));
	return (0);
}

static int	is_redirection_token(int type)
{
	return (type == IN_REDIRECT || type == OUT_REDIRECT
		|| type == APPEND || type == HEREDOC);
}

static t_token	*handle_redirection_parsing(t_data *data, t_command **current_cmd, t_command **head, t_token *current, int *error_flag)
{
	*error_flag = handle_redirection_token(data, current_cmd, head, current);
	if (current->next && current->next->next)
		return (current->next->next);
	return (NULL);
}

static void	remove_current_command(t_command **head, t_command **current_cmd)
{
	t_command	*prev;
	t_command	*to_remove;

	if (!*current_cmd)
		return;
	to_remove = *current_cmd;
	if (*head == *current_cmd)
	{
		*head = (*current_cmd)->next;
		*current_cmd = NULL;
		return;
	}
	prev = *head;
	while (prev && prev->next != *current_cmd)
		prev = prev->next;
	if (prev)
	{
		prev->next = (*current_cmd)->next;
		*current_cmd = NULL;
	}
}

static t_token	*process_single_token(t_data *data, t_command **current_cmd, t_command **head, t_token *current, int *error_flag)
{
	if (current->type == WORD)
	{
		*error_flag = handle_word_token(data, current_cmd, head, current);
		if (*error_flag)
		{
			remove_current_command(head, current_cmd);
			while (current && current->type != PIPE)
				current = current->next;
			return (current);
		}
		return (current->next);
	}
	else if (is_redirection_token(current->type))
	{
		t_token *next = handle_redirection_parsing(data, current_cmd, head, current, error_flag);
		if (*error_flag)
		{
			remove_current_command(head, current_cmd);
			while (current && current->type != PIPE)
				current = current->next;
			return (current);
		}
		return (next);
	}
	else if (current->type == PIPE)
	{
		*current_cmd = parse_pipe(data, *current_cmd);
		return (current->next);
	}
	else
		return (current->next);
}

t_command	*parse_tokens(t_data *data)
{
	t_token		*current;
	t_command	*head;
	t_command	*current_command;
	int			error_flag;

	head = NULL;
	current_command = NULL;
	current = data->token_list;
	while (current)
	{
		error_flag = 0;
		current = process_single_token(data, &current_command, &head, current, &error_flag);
	}
	return (head);
}

static void	link_command_to_list(t_command **head, t_command *new_cmd)
{
	t_command	*last_cmd;

	if (!*head)
		*head = new_cmd;
	else
	{
		last_cmd = *head;
		while (last_cmd->next)
			last_cmd = last_cmd->next;
		last_cmd->next = new_cmd;
	}
}

t_command	*parse_command(t_data *data, t_command **head, t_command *current_command)
{
	data = 0;
	if (!current_command)
	{
		current_command = g_malloc(sizeof(t_command), MALLOC);
		if (!current_command)
			return (NULL);
		ft_bzero(current_command, sizeof(t_command));
		link_command_to_list(head, current_command);
	}
	return (current_command);
}

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

	data = 0;
	if (!cmd || !value)
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

static int	open_input_file(char *file)
{
	return (open(file, O_RDONLY));
}

static int	open_output_file(char *file)
{
	return (open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644));
}

static int	open_append_file(char *file)
{
	return (open(file, O_WRONLY | O_CREAT | O_APPEND, 0644));
}

static int	open_redirection_file(t_redirection *redir)
{
	if (redir->type == IN_REDIRECT)
		return (open_input_file(redir->file));
	else if (redir->type == OUT_REDIRECT)
		return (open_output_file(redir->file)); 
	else if (redir->type == APPEND)
		return (open_append_file(redir->file));
	else if (redir->type == HEREDOC)
		return (-3);
	return (-2);
}

static void	add_redirection_to_list(t_command *cmd, t_redirection *new_redir)
{
	t_redirection	*last_redir;

	if (!cmd->redirects)
		cmd->redirects = new_redir;
	else
	{
		last_redir = cmd->redirects;
		while (last_redir->next)
			last_redir = last_redir->next;
		last_redir->next = new_redir;
	}
}

static t_redirection	*create_redirection(t_data *data, t_token *current)
{
	t_redirection	*new_redir;

	data = 0;
	new_redir = g_malloc(sizeof(t_redirection), MALLOC);
	if (!new_redir)
		return (NULL);
	ft_bzero(new_redir, sizeof(t_redirection));
	new_redir->type = current->type;
	new_redir->file = ft_strdup(current->next->value);
//	new_redir->fd = open_redirection_file(new_redir);
	return (new_redir);
}

static int	check_redirection_errors(t_token *current)
{
	if (!current || !current->next)
	{
		printf("minishell: syntax error near unexpected token `newline'\n");
		return (1);
	}
	if (current->next->ambiguous)
	{
		printf("minishell: %s: ambiguous redirect\n", current->next->value);
		return (1);
	}
	return (0);
}

int	parse_redirection(t_data *data, t_command *cmd, t_token *current)
{
	t_redirection	*new_redir;

	if (!cmd)
		return (0);
	if (check_redirection_errors(current))
		return (1);
	new_redir = create_redirection(data, current);
	if (!new_redir)
		return (0);
	add_redirection_to_list(cmd, new_redir);
	return (0);
}

t_command	*parse_pipe(t_data *data, t_command *current_command)
{
	data = 0;
	if (!current_command)
		return (NULL);
	if (!current_command->next)
		return (NULL);
	current_command = current_command->next;
	ft_bzero(current_command, sizeof(t_command));
	return (current_command);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	if (!s)
		return ;
	ptr = (unsigned char *)s;
	i = 0;
	while (i < n)
		ptr[i++] = 0;
}