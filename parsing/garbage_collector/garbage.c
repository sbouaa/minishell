/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbouaa <sbouaa@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 11:43:48 by sbouaa            #+#    #+#             */
/*   Updated: 2025/06/13 11:43:50 by sbouaa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void gc_add(t_gc *gc, void *ptr)
{
    if (!gc || !ptr)
        return;
    t_node *new_node = (t_node *)malloc(sizeof(t_node));
    if (!new_node)
        return;
    new_node->ptr = ptr;
    new_node->next = gc->head;
    gc->head = new_node;
}

void *gc_malloc(t_gc *gc, unsigned int size)
{
    if (!gc)
        return NULL;
    void *ptr = malloc(size);
    if (!ptr)
        return NULL;
    gc_add(gc, ptr);
    return ptr;
}

void gc_free_all(t_gc *gc)
{
    t_node *current;
    t_node *next;

    if (!gc)
        return;
    current = gc->head;
    while (current)
    {
        next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    gc->head = NULL;
}
