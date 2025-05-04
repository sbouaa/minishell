#include "minishell.h"

int	init_data(t_data *data)
{
    data->prompt = NULL;
	data->gc.head = NULL;
	data->token_list = NULL;
	data->cmd = NULL;
	return (0);
}