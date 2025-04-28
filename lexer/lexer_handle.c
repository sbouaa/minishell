#include "../minishell.h"

int	handle_quotes(char *line, int i, int *index_pair,
		t_token_type *type)
{
	int	end;

	end = bunny_ears(line, i + 1, line[i]);
	if (end == -1)
		return (-1);
	index_pair[0] = i;
	index_pair[1] = end + 1;
	*type = QUOTE;
	return (1);
}

int	handle_redirection(char *line, int i, int *index_pair,
		t_token_type *type)
{
	if (line[i] == '<' && line[i + 1] == '<')
	{
		index_pair[0] = i;
		index_pair[1] = i + 2;
		*type = HEREDOC;
	}
	else if (line[i] == '>' && line[i + 1] == '>')
	{
		index_pair[0] = i;
		index_pair[1] = i + 2;
		*type = APPEND;
	}
	else if (line[i] == '<')
	{
		index_pair[0] = i;
		index_pair[1] = i + 1;
		*type = IN_REDIRECT;
	}
	else if (line[i] == '>')
	{
		index_pair[0] = i;
		index_pair[1] = i + 1;
		*type = OUT_REDIRECT;
	}
	return (1);
}

int	handle_pipe(int i, int *index_pair, t_token_type *type)
{
	index_pair[0] = i;
	index_pair[1] = i + 1;
	*type = PIPE;
	return (1);
}