#include "../minishell.h"

void	print_parsed_commands(t_command *cmd)
{
    t_redirection	*redir;

    while (cmd)
    {
        printf("Command:\n");
        for (int i = 0; cmd->args && cmd->args[i]; i++)
            printf("  Arg[%d]: %s\n", i, cmd->args[i]);
        redir = cmd->redirects;
        while (redir)
        {
            printf("  Redirection:\n");
            printf("    Type: %d\n", redir->type);
            printf("    File: %s\n", redir->file);
            printf("    FD: %d\n", redir->fd);
            redir = redir->next;
        }
        cmd = cmd->next;
    }
}

int	main(void)
{
	t_data data;
	t_command	*commands;
	if (init_data(&data) != 0)
		return (1);

	while (1)
	{
		data.prompt = readline("minishell$ ");
		if (!data.prompt)
			break ;
		if (data.prompt[0] != '\0')
		{
			add_history(data.prompt);
			if (!lexer(&data) && !check_syntax_errors(&data))
			{
				expand(&data);
				commands = parse_tokens(&data);
                //print_parsed_commands(commands);
			}
		}
		free(data.prompt);
	}
	//gc_free_all(&data.gc);
	return (0);
}