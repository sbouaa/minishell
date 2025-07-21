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

void	print_tokens(t_token *token)
{
    int	i = 0;

    while (token)
    {
        printf("Token[%d]:\n", i);
        printf("  Type      : %d\n", token->type);
        printf("  Value     : %s\n", token->value);
        printf("  Ambiguous : %d\n", token->ambiguous);
        token = token->next;
        i++;
    }
}

void	handle_prompt(t_data *data, t_env *env)
{
    data->prompt = readline("minishell > ");
    if (!data->prompt)
    {
        free(data->prompt);
        return ;
    }
    if (data->prompt[0] != '\0')
    {
        add_history(data->prompt);
        if (lexer(data))
        {
            data->token_list = NULL;
            return;
        }
        if (check_syntax_errors(data))
        {
            data->token_list = NULL;
            return;
        }
        data->prompt = expand(data->prompt, env);
        lexer(data);
        expand_redirections(data->token_list, data->env);
        print_tokens(data->token_list);
        
    }
}

void	execute_commands(t_data *data)
{
    t_command *commands;

    commands = parse_tokens(data);
    data->exit_status = ft_begin_exec(commands, &data->env);
    print_parsed_commands(commands);
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_data data;

    if (!isatty(0))
        return (1);

    if (init_data(&data) != 0)
    {
        fprintf(stderr, "Error: Failed to initialize data.\n");
        return (1);
    }
    data.env = init_data_exec(env);
    while (1)
    {
        handle_prompt(&data, data.env);
        if (data.prompt && data.prompt[0] != '\0')
        {
            data.token_list = quote_remove(&data);
            execute_commands(&data);
        }
    }
    gc_malloc(0, FREE);
    g_malloc(0, FREE);
    return (0);
}