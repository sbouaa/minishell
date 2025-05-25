#include "minishell.h"

int	main(void)
{
	t_data	data;

	if (init_data(&data) != 0)
		return (1);

	while (1)
	{
		data.prompt = readline("minishell$ ");
		if (!data.prompt)
			break ;
		if (data.prompt[0] != '\0')
		{
			add_history(data.prompt);
			if (lexer(&data) == 0 && check_syntax_errors(&data) == 0)
			{
				expand(&data);
				print_token_list(&data);
			}
		}
		free(data.prompt);
	}
	gc_free_all(&data.gc);
	return (0);
}