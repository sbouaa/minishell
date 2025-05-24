#include "../minishell.h"

void parsing(t_data *data)
{
    t_token *current = data->token_list;
    t_args *args = create_args_node(data);
    args->args = create_arg_node(data);

}