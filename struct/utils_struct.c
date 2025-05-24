#include "../minishell.h"

t_arg *create_arg_node(t_data *data, const char *value)
{
    t_arg *new = gc_malloc(&data->gc, sizeof(t_arg));
    if (!new)
        return NULL;
    new->value = ft_strdup(value, data);
    new->next = NULL;
    return new;
}

t_args *create_args_node(t_data *data)
{
    t_args *new = gc_malloc(&data->gc, sizeof(t_args));
    if (!new)
        return NULL;
    new->args = NULL;
    new->next = NULL;
    return new;
}

void add_arg(t_data *data, t_args *cmd, const char *value)
{
    t_arg *new = create_arg_node(data, value);
    if (!cmd->args)
        cmd->args = new;
    else
    {
        t_arg *tmp = cmd->args;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new;
    }
}

void add_args(t_data *data, t_args **head)
{
	t_args *new = create_args_node(data);
	if (!new)
		return;
	if (!*head)
		*head = new;
	else
	{
		t_args *temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}


