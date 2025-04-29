/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 01:55:25 by sbouaa            #+#    #+#             */
/*   Updated: 2025/04/29 19:47:18 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*mn_lstnew(char *key, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	mn_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}
void	ft_clear(t_env **all)
{
	t_env	*root;
	t_env	*temp;

	if (!all || !*all)
		return ;
	root = *all;
	while (root != NULL)
	{
		temp = root->next;
		free(root);
		root = temp;
	}
	*all = NULL;
}

void	ft_clean(char **p)
{
	int	i;

	i = 0;
	while (p[i])
		(free(p[i]), i++);
	free(p);
	p = NULL;
	return ;
}
