#include "../minishell.h"

int	ft_check_expand(char *str, bool *in_double_quote, bool *in_single_quote)
{
	int i = 0;

	while (str && str[i])
	{
		if (!(*in_single_quote) && !(*in_double_quote) && str[i] == '"')
			*in_double_quote = true;
		else if (!(*in_double_quote) && !(*in_single_quote) && str[i] == '\'')
			*in_single_quote = true;
		else if (*in_double_quote && str[i] == '"')
			*in_double_quote = false;
		else if (*in_single_quote && str[i] == '\'')
			*in_single_quote = false;

		// Uncomment for debugging:
		if (str[i] == '$' && !(*in_single_quote))
		    printf("Found expandable $ at position: %d\n", i);
		printf("char: %c, dbl: %d, sgl: %d\n", str[i], *in_double_quote, *in_single_quote);

		i++;
	}
	return (!(*in_double_quote));
}

int expand(t_data *data)
{
	t_token *current = data->token_list;
	bool in_double_quote = false;
	bool in_single_quote = false;

	while (current)
	{
		ft_check_expand(current->value, &in_double_quote, &in_single_quote);
		current = current->next;
	}

	return (0);
}
