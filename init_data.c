#include "minishell.h"

int	init_data(t_data *data)
{
    data->prompt = NULL;
	data->gc.head = NULL;
	data->token_list = NULL;
	if (!getcwd(data->working_dir, sizeof(data->working_dir)))
	{
		perror("getcwd");
		return (1);
	}
	if (tcgetattr(STDERR_FILENO, &data->original_term) != 0
		|| tcgetattr(STDERR_FILENO, &data->shell_term) != 0)
		return (1);
	return (0);
}