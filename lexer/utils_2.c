#include "../minishell.h"

int	is_token(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n' || 
			c == '\v' || c == '\f' || c == '\r');
}

int	is_quote(int c)
{
	return (c == '\'' || c == '\"');
}

char	*get_token_type_string(t_token_type type)
{
	static char *type_strings[] = {
		"PIPE",
		"IN_REDIRECT",
		"OUT_REDIRECT",
		"HEREDOC",
		"APPEND",
		"DBQUOTE",
		"SIQUOTE",
		"WORD",
		"SPACE",
		"EXPAND"
	};

	if (type >= 0 && type <= EXPAND)
		return (type_strings[type]);
	return ("UNKNOWN");
}

void	print_token_list(t_data *data)
{
	t_token	*current;
	int		i;

	if (!data || !data->token_list)
	{
		printf("No tokens to display\n");
		return;
	}

	i = 0;
	current = data->token_list;
	printf("\nToken List:\n");
	printf("----------------------------------------\n");
	while (current)
	{
		printf("Token %d:\n", i++);
		printf("  Type: %s\n", get_token_type_string(current->type));
		printf("  Value: |%s|\n", current->value ? current->value : "NULL");
		printf("----------------------------------------\n");
		current = current->next;
	}
}