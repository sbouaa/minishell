#include "../minishell.h"

static int	count_words(t_token *token)
{
	int	count;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (token->type == WORD)
			count++;
		token = token->next;
	}
	return (count);
}

static t_cmd	*build_command(t_data *data, t_token **curr)
{
	int		word_count;
	char	**cmd_arr;
	int		i;
	t_cmd	*cmd;

	word_count = count_words(*curr);
	cmd_arr = gc_malloc(&data->gc, sizeof(char *) * (word_count + 1));
	i = 0;
	while (*curr && (*curr)->type != PIPE)
	{
		if ((*curr)->type == WORD)
		{
			cmd_arr[i++] = (*curr)->value;
		}
		*curr = (*curr)->next;
	}
	cmd_arr[i] = NULL;
	cmd = gc_malloc(&data->gc, sizeof(t_cmd));
	cmd->cmd = cmd_arr;
	cmd->n_cmd = word_count;
	cmd->next = NULL;
	if (*curr && (*curr)->type == PIPE)
		*curr = (*curr)->next;
	return (cmd);
}

void	parse_command_list(t_data *data)
{
	t_token	*curr;
	t_cmd	*head;
	t_cmd	*last;
	t_cmd	*cmd;

	curr = data->token_list;
	head = NULL;
	last = NULL;
	while (curr)
	{
		cmd = build_command(data, &curr);
		if (!head)
			head = cmd;
		else
			last->next = cmd;
		last = cmd;
	}
	data->command_list = head;
}

void	print_commands(t_cmd *cmd_list)
{
	int	i;
	int	cmd_num;

	cmd_num = 1;
	while (cmd_list)
	{
		printf("Command %d: ", cmd_num++);
		for (i = 0; i < cmd_list->n_cmd; i++)
		{
			printf("[%s] ", cmd_list->cmd[i]);
		}
		printf("\n");
		cmd_list = cmd_list->next;
	}
}
