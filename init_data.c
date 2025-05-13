#include "minishell.h"

int	init_data(t_data *data)
{
    data->prompt = NULL;
	data->gc.head = NULL;
	data->token_list = NULL;
	data->cmd_list = NULL;
	return (0);
}