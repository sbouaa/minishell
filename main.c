#include "minishell.h"


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
        
    }
}

void	execute_commands(t_data *data)
{
    t_command *commands;

    commands = parse_tokens(data);
    data->exit_status = ft_begin_exec(commands, &data->env);
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
