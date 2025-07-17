#include "../../minishell.h"

static void	update_quote_states(char c, int *in_s, int *in_d)
{
	if (!*in_s && !*in_d && c == '\'')
		*in_s = 1;
	else if (!*in_s && !*in_d && c == '"')
		*in_d = 1;
	else if (*in_s && c == '\'')
		*in_s = 0;
	else if (*in_d && c == '"')
		*in_d = 0;
}

static void	process_char(t_expand *exp)
{
	char	tmp[2];

	tmp[0] = exp->str[exp->i];
	tmp[1] = '\0';
	exp->result = ft_strjoin(exp->result, tmp);
	exp->i++;
}

static char	*handle_var_expansion(char *str, int *i)
{
	char	*var;
	char	*value;
	int		start;

	if (!str[*i + 1] || (!ft_isalnum(str[*i + 1]) && str[*i + 1] != '_'))
		return (NULL);
	(*i)++;
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	value = getenv(var);
	if (!value)
		return (ft_strdup(""));
	return (ft_strdup(value));
}

static int	is_redirect(char *s, int i)
{
	if ((s[i] == '>' || s[i] == '<') && s[i + 1] == s[i])
		return (2);
	if (s[i] == '>' || s[i] == '<')
		return (1);
	return (0);
}

static void	skip_redirect_part(t_expand *exp)
{
	int		r_len;
	char	*redir;

	r_len = is_redirect(exp->str, exp->i);
	redir = ft_substr(exp->str, exp->i, r_len);
	exp->result = ft_strjoin(exp->result, redir);
	exp->i += r_len;
	while (exp->str[exp->i] == ' ' || exp->str[exp->i] == '\t')
		process_char(exp);
	while (exp->str[exp->i]
		&& exp->str[exp->i] != ' ' && exp->str[exp->i] != '\t')
		process_char(exp);
}

static void	process_dollar(t_expand *exp)
{
	if (exp->str[exp->i + 1] == '$')
	{
		exp->i += 2;
		return ;
	}
	if (exp->str[exp->i + 1]
		&& (exp->str[exp->i + 1] == '\'' || exp->str[exp->i + 1] == '"')
		&& !exp->in_double)
	{
		exp->i++;
		return ;
	}
	exp->expand = handle_var_expansion(exp->str, &exp->i);
	if (exp->expand)
	{
		exp->result = ft_strjoin(exp->result, exp->expand);
		return ;
	}
	process_char(exp);
}

void expand_redirections(t_token *token)
{
    while (token)
    {
        if ((token->type == IN_REDIRECT || token->type == OUT_REDIRECT
             || token->type == APPEND) && token->next)
        {
            token = token->next;
            if (token->value && ft_strchr(token->value, '$'))
            {
                char *expanded = expand(token->value);
                if (!expanded || expanded[0] == '\0' || ft_strchr(expanded, ' '))
                {
                    token->ambiguous = true;
                    token->value = NULL; // Set value to NULL for invalid expansions
                }
                else
                {
                    token->value = expanded;
                }
            }
        }
        else if (token->type == HEREDOC && token->next)
        {
            token = token->next;
        }
        token = token->next;
    }
}


char	*expand(char *prompt)
{
	t_expand	exp;

	exp.i = 0;
	exp.in_single = 0;
	exp.in_double = 0;
	exp.str = (char *)prompt;
	exp.result = ft_strdup("");
	while (exp.str[exp.i])
	{
		update_quote_states(exp.str[exp.i], &exp.in_single, &exp.in_double);
		if (!exp.in_single && !exp.in_double
			&& is_redirect(exp.str, exp.i))
			skip_redirect_part(&exp);
		else if (exp.str[exp.i] == '$' && !exp.in_single)
			process_dollar(&exp);
		else
			process_char(&exp);
	}
	return (exp.result);
}
