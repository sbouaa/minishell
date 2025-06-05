#include "../minishell.h"
#include <fcntl.h>
#include <unistd.h>

// Function to parse tokens into commands
t_command	*parse_tokens(t_data *data)
{
    t_token		*current;
    t_command	*head;
    t_command	*current_command;

    head = NULL;
    current_command = NULL;
    current = data->token_list;
    while (current)
    {
        if (current->type == WORD)
        {
            // Parse the command and add arguments
            if (!current_command)
                current_command = parse_command(data, &head, current_command);
            else
                add_argument(data, current_command, current->value);
            current = current->next;
        }
        else if (current->type == IN_REDIRECT || current->type == OUT_REDIRECT
            || current->type == APPEND || current->type == HEREDOC)
        {
            // Parse redirections
            parse_redirection(data, current_command, current);
            current = current->next->next; // Skip the filename token
        }
        else if (current->type == PIPE)
        {
            // Handle pipes by creating a new command
            current_command = parse_pipe(data, current_command);
            current = current->next;
        }
    }
    return (head);
}

// Function to parse a command and allocate memory
t_command	*parse_command(t_data *data, t_command **head, t_command *current_command)
{
    if (!current_command)
    {
        // Allocate memory for the new command using gc_malloc
        current_command = gc_malloc(&data->gc, sizeof(t_command));
        if (!current_command)
            return (NULL);
        ft_bzero(current_command, sizeof(t_command)); // Initialize memory to zero
        if (!*head)
            *head = current_command; // Set the head of the command list
        else
            current_command->next = NULL;
    }

    // Allocate memory for the arguments array (initial size 2: command + NULL)
    current_command->args = gc_malloc(&data->gc, sizeof(char *) * 2);
    if (!current_command->args)
        return (NULL);

    // Add the command name
    if (data->token_list->value)
        current_command->args[0] = ft_strdup(data->token_list->value, data);
    current_command->args[1] = NULL;

    return (current_command);
}

// Function to add an argument to a command
void	add_argument(t_data *data, t_command *cmd, char *value)
{
    size_t	arg_count;
    char	**new_args;

    // Count existing arguments
    arg_count = 0;
    if (cmd->args)
    {
        while (cmd->args[arg_count])
            arg_count++;
    }

    // Allocate memory for the new arguments array
    new_args = gc_malloc(&data->gc, sizeof(char *) * (arg_count + 2));
    if (!new_args)
        return;

    // Copy existing arguments to the new array
    for (size_t i = 0; i < arg_count; i++)
        new_args[i] = cmd->args[i];

    // Add the new argument and NULL-terminate the array
    if (value)
        new_args[arg_count] = ft_strdup(value, data);
    new_args[arg_count + 1] = NULL;

    // Update the args pointer
    cmd->args = new_args;
}

// Function to parse redirections
void	parse_redirection(t_data *data, t_command *cmd, t_token *current)
{
    t_redirection	*new_redir;
    t_redirection	*last_redir;

    // Allocate memory for the new redirection using gc_malloc
    new_redir = gc_malloc(&data->gc, sizeof(t_redirection));
    if (!new_redir)
        return;
    ft_bzero(new_redir, sizeof(t_redirection)); // Initialize memory to zero

    // Set redirection type and file
    new_redir->type = current->type;
    new_redir->file = ft_strdup(current->next->value, data);
    new_redir->fd = -1;

    // Open the file based on the redirection type
    if (new_redir->type == IN_REDIRECT)
        new_redir->fd = open(new_redir->file, O_RDONLY);
    else if (new_redir->type == OUT_REDIRECT)
        new_redir->fd = open(new_redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else if (new_redir->type == APPEND)
        new_redir->fd = open(new_redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (new_redir->type == HEREDOC)
        new_redir->fd = -1; // Handle HEREDOC separately if needed

    // Handle file open errors
    if (new_redir->fd == -1 && new_redir->type != HEREDOC)
        perror("open");

    // Add the new redirection to the command's redirection list
    if (!cmd->redirects)
        cmd->redirects = new_redir;
    else
    {
        last_redir = cmd->redirects;
        while (last_redir->next)
            last_redir = last_redir->next;
        last_redir->next = new_redir;
    }
}

// Function to handle pipes
t_command	*parse_pipe(t_data *data, t_command *current_command)
{
    if (current_command)
        current_command->next = gc_malloc(&data->gc, sizeof(t_command));
    if (!current_command->next)
        return (NULL);
    current_command = current_command->next;
    ft_bzero(current_command, sizeof(t_command));
    return (current_command);
}

// Utility function: ft_bzero
void	ft_bzero(void *s, size_t n)
{
    unsigned char	*ptr;
    size_t			i;

    ptr = (unsigned char *)s;
    i = 0;
    while (i < n)
        ptr[i++] = 0;
}