#include "../minishell.h"

int	ft_strchr_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_check_expand(char *current, bool *flag_dbquote, bool *flag_sgquote)
{
	int	i;
	i = 0;
    printf("%s\n",current);
	while (current && current[i])
	{
		if (!(*flag_sgquote) && !(*flag_dbquote) && current[i] == '"')
			*flag_dbquote = 1;
		else if (!(*flag_dbquote) && !(*flag_sgquote) &&current[i] == '\'')
			*flag_sgquote = 1;
        else if ((*flag_dbquote) && !(*flag_sgquote) && current[i] == '"')
            *flag_dbquote = 0;
        else if ((*flag_sgquote) && !(*flag_dbquote) && current[i] == '\'')
            *flag_sgquote = 0;
        if((current[i] == '$' && !(*flag_sgquote))){
            printf("position if expand or not :%d\n", i);
        }
        // printf("%c\n",current[i]);
        // printf("dblquote: %d\n", *flag_dbquote);
        // printf("sglquote: %d\n", *flag_sgquote);
		i++;
	}
    if (*flag_dbquote)
        return (0);
    else
        return (1);
}
int	expand(t_data *data)
{
	int i;
	i = 0;
	char *quote;
    int count = 0;
	bool flag_dbquote = 0;
	bool flag_sgquote = 0;

	t_token *current = data->token_list;
	while (current)
	{
		ft_check_expand(current->value, &flag_dbquote, &flag_sgquote);
		current = current->next;
	}
	return (0);
}