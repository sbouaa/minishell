#include "minishell.h"

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

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_data data;
    t_command *commands;
    t_dd *datas;

    if (!isatty(0))
        return (1);
    if (init_data(&data) != 0)
        return (1);
    datas = init_data_exec(NULL, env);
    data.env = datas->env;
    t_env *current_env = data.env;

    while (1)
    {
        data.prompt = readline("\033[1;32mminishell > \033[0m");
        if (!data.prompt)
            break;
        if (data.prompt[0] != '\0')
        {
            add_history(data.prompt);
            if (!lexer(&data) && !check_syntax_errors(&data))
            {
                expand(&data);
                commands = parse_tokens(&data);
                data.exit_status = ft_begin_exec(commands, current_env);
                current_env = data.env;
                //print_parsed_commands(commands);
                g_malloc(0, FREE);
            }
        }
    }
    return (0);
}