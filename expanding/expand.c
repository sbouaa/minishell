#include "../minishell.h"

int ft_strchr_dollar(char *str)
{
    int i = 0;
    while(str[i])
    {
        if (str[i] == '$')
            return 1;
        i++;
    }
    return 0;
}

int expand(t_data *data)
{
    int i;
    i = 0;
    char *quote;
    t_token *current = data->token_list;
    while(current->next != NULL)
    {
        check_quote_type();

    }
}