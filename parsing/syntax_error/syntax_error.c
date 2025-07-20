#include "../../minishell.h"

 int	is_redirection(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == IN_REDIRECT || token->type == OUT_REDIRECT
		|| token->type == HEREDOC || token->type == APPEND);
}

 int	is_word_token(t_token *token)
{
	if (!token)
		return (0);
	return (token->type == WORD);
}

 int	check_pipe_errors(t_token *token)
{
	if (token->type == PIPE)
	{
		if (!token->next || token->next->type == PIPE)
		{
			printf("Syntax error: unexpected token `|'\n");
			return (1);
		}
	}
	return (0);
}

 int	check_redirection_errors(t_token *token)
{
	if (is_redirection(token))
	{
		if (!token->next || !is_word_token(token->next))
		{
			printf("Syntax error: expected filename after redirection\n");
			return (1);
		}
	}
	return (0);
}

int	check_syntax_errors(t_data *data)
{
	t_token	*cur;

	cur = data->token_list;
	if (!cur)
		return (0);
	if (cur->type == PIPE)
	{
		printf("Syntax error: unexpected token `|'\n");
		return (1);
	}
	while (cur)
	{
		if (check_pipe_errors(cur) || check_redirection_errors(cur))
			return (1);
		cur = cur->next;
	}
	cur = data->token_list;
	while (cur && cur->next)
		cur = cur->next;
	if (cur && cur->type == PIPE)
	{
		printf("Syntax error: unexpected end after `|'\n");
		return (1);
	}
	return (0);
} 