#include "../minishell.h"

int	init_data(t_data *data)
{
	if (!data)
		return (1);
	data->prompt = NULL;
	data->token_list = NULL;
	data->syntax_error = 0;
	data->gc.head = NULL;
	data->commands = NULL;
	return (0);
}