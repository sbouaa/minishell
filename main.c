#include "minishell.h"

void	print_parsed_commands(t_command *cmd)
{
    t_redirection	*redir;

    while (cmd)
    {
        ft_printf("Command:\n");
        for (int i = 0; cmd->args && cmd->args[i]; i++)
            ft_printf("  Arg[%d]: %s\n", i, cmd->args[i]);
        redir = cmd->redirects;
        while (redir)
        {
            ft_printf("  Redirection:\n");
            ft_printf("    Type: %d\n", redir->type);
            ft_printf("    File: %s\n", redir->file);
            ft_printf("    FD: %d\n", redir->fd);
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
        ft_printf("Token[%d]:\n", i);
        ft_printf("  Type      : %d\n", token->type);
        ft_printf("  Value     : %s\n", token->value);
        ft_printf("  Ambiguous : %d\n", token->ambiguous);
        token = token->next;
        i++;
    }
}

int	handle_prompt(t_data *data, t_env *env)
{
    data->prompt = readline("minishell > ");
    if (!data->prompt)
    {
        free(data->prompt);
        return (33);
    }
    if (data->prompt[0] != '\0')
    {
        add_history(data->prompt);
        if (lexer(data))
        {
            data->token_list = NULL;
            return (1);
        }
        if (check_syntax_errors(data))
        {
            data->token_list = NULL;
            return (1);
        }
        data->prompt = expand(data->prompt, env, data);
        lexer(data);
        expand_redirections(data->token_list, data->env, data);
    }
    else
        return (2);
    return (0);
}

void	execute_commands(t_data *data)
{
    t_command *commands;

    commands = parse_tokens(data);
    if (commands)
        data->exit_status = ft_begin_exec(commands, &data->env);
}

void    set_e_status(int set, int status, t_data *data)
{
    static t_data  *ptr;

    if (set)
        ptr = data;
    ptr->exit_status = status;
}

void    signal_handle(int sig)
{
    if (sig == SIGQUIT)
        return ;
    ft_putstr_fd("\n", 1);
    rl_replace_line("", 1);
    rl_on_new_line();
    rl_redisplay();
    set_e_status(0, 130, NULL);
    sig = 1;
}



int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    t_data data;
    int status;

    if (!isatty(0))
        return (1);
    set_e_status(1, 0, &data);
    signal(SIGINT, &signal_handle);
    signal(SIGQUIT , &signal_handle);
    if (init_data(&data) != 0)
        return (1);
    data.env = init_data_exec(env);
    while (1)
    {
        status = handle_prompt(&data, data.env);
        if (status == 1 || status == 2)
            continue;
        else if (status == 33)
            break ;
        data.token_list = quote_remove(&data);
        execute_commands(&data);
    }
    gc_malloc(0, FREE);
    g_malloc(0, FREE);
    return (data.exit_status);
}
