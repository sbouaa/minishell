#include "minishell.h"

static int	handle_line(t_data *data)
{
	if (data->prompt)
	{
		free(data->prompt);
		data->prompt = NULL;
	}
	data->prompt = readline("minishell$ ");
	if (!data->prompt)
	{
		printf("exit\n");
		return (-1);
	}
	if (*data->prompt)
		add_history(data->prompt);
	return (0);
}

static int	main_loop(t_data *data)
{
	while (1)
	{
		if (handle_line(data) == -1)
			break;
        if(lexer(data) == 0 && check_syntax_errors(data) == 0){
			print_tokens(data);
		}
		continue;
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argc;
	(void)argv;
    (void)envp;
	if (init_data(&data) != 0)
		return (EXIT_FAILURE);
	main_loop(&data);
	gc_free_all(&data.gc);
	return (EXIT_SUCCESS);
}