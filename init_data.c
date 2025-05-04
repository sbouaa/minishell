#include "minishell.h"

int	init_data(t_data *data)
{
    data->prompt = NULL;
	data->gc.head = NULL;
	data->token_list = NULL;
	data->cmd = NULL;
	data->syntax_error = 0;
	return (0);
}