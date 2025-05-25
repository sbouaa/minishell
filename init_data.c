#include "minishell.h"

int	init_data(t_data *data)
{
	data->prompt = NULL;
	data->gc.head = NULL;
	data->token_list = NULL;
	data->env = NULL;
	return (0);
}

t_env	*create_node(t_data *data, const char *key, const char *value)
{
	t_env	*node;

	node = (t_env *)gc_malloc(&data->gc, sizeof(t_env));
	if (!node)
		return (NULL);
	if (key)
		node->key = ft_strdup(key, data);
	else
		node->key = NULL;
	if (value)
		node->value = ft_strdup(value, data);
	else
		node->value = NULL;
	node->next = NULL;
	return (node);
}

void	add_to_back(t_data *data, const char *key, const char *value)
{
	t_env	*new_node;
	t_env	*current;

	new_node = create_node(data, key, value);
	if (!new_node)
		return ;
	if (data->env == NULL)
	{
		data->env = new_node;
		return ;
	}
	current = data->env;
	while (current->next != NULL)
		current = current->next;
	current->next = new_node;
}

void	print_nodes(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

char	*search_node(t_data *data, const char *key)
{
	t_env	*current;

	current = data->env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

static void	get_key(t_data *data, char *env, char **key, int *i)
{
	int	start;

	start = 0;
	while (env[*i] && env[*i] != '=')
		(*i)++;
	*key = ft_substr(data, env, start, *i - start);
}

static void	get_value(t_data *data, char *env, char **value, int *i)
{
	int	start;

	if (env[*i] != '=')
	{
		*value = NULL;
		return ;
	}
	(*i)++;
	start = *i;
	while (env[*i])
		(*i)++;
	*value = ft_substr(data, env, start, *i - start);
}

void	split_key_value(t_data *data, char *env, char **key, char **value)
{
	int	i;

	i = 0;
	get_key(data, env, key, &i);
	get_value(data, env, value, &i);
}

void	envp_init(t_data *data, char **envp)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		key = NULL;
		value = NULL;
		split_key_value(data, envp[i], &key, &value);
		add_to_back(data, key, value);
		i++;
	}
}
