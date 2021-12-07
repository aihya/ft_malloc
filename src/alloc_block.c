/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:07:15 by aihya             #+#    #+#             */
/*   Updated: 2021/12/06 17:15:47 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_block	*split_block(t_block *block, size_t size)
{
	t_block	*next;

	if (block)
	{
		next = NULL;
		block->free = FALSE;
		if (block->size != size)
		{
			next = (t_block *)((void *)block + size);
			next->size = block->size - size;
			next->free = TRUE;
			next->next = block->next;
			block->size = size;
			block->next = next;
		}
	}
	return (block);
}

static t_zone	*init_head(t_zone **head, t_zone **tail, int type)
{
	if (*head == NULL)
	{
		*head = new_zone(zone_size(type), type);
		if (*head == NULL)
			return (NULL);
		*tail = *head;
	}
	return (*head);
}

static t_block	*alloc(size_t size, t_zone **head, t_zone **tail, int type)
{
	t_block	*best;

	// Ckeck for head if it exists, and initialize it if it doesn't.
	if (init_head(head, tail, type) == NULL)
		return (NULL);

	// Find the best block and return it after spliting.
	best = best_fit(size, *head, type);
	if (best)
		return (split_block(best, size));

	// Allocate new zone and use it's free block as the best block.
	(*tail)->next = new_zone(zone_size(type), type);
	if ((*tail)->next == NULL)
		return (NULL);	
	(*tail)->next->prev = *tail;
	(*tail) = (*tail)->next;
	return (split_block((t_block *)shift_zone(*tail), size));
}

void		*alloc_block(size_t size, int type)
{
	t_zone	**head;
	t_zone	**tail;

	// Get the corresponding head and tail for the specified type.
	head = &g_mem.tiny;
	tail = &g_mem.tiny_end;
	if (type == SMALL)
	{
		head = &g_mem.small;
		tail = &g_mem.small_end;
	}
	return (shift_block(alloc(size, head, tail, type)));
}