/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:40:17 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 19:00:35 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	free_zone(t_zone *zone, t_zone **head, t_zone **tail)
{
	if (zone->prev)
		zone->prev->next = zone->next;
	else
	{
		*head = zone->next;
		(*head) && ((*head)->prev = NULL);
	}
	if (zone->next)
		zone->next->prev = zone->prev;
	else
	{
		*tail = zone->prev;
		(*tail) && ((*tail)->next = NULL);
	}
	munmap(zone, zone->size);
	zone = NULL;
}

void	free_block(t_block *block, t_zone *zone, int type)
{
	block->free = TRUE;
	if (defragement(zone) == zone->size - sizeof(t_zone))
	{
		if (type == TINY)
			free_zone(zone, &g_mem.tiny, &g_mem.tiny_end);
		else
			free_zone(zone, &g_mem.small, &g_mem.small_end);
	}
}

void	ft_free(void *ptr, t_zone *hint)
{
	t_zone	*zone;
	int		type;
	int		isfree;

	init_consts();
	zone = NULL;
	type = -1;
	isfree = FALSE;
	if (hint)
	{
		zone = hint;
		type = zone_type(hint);
	}
	if (hint || search(ptr, &zone, &type, &isfree))
	{
		if (!isfree && (type == TINY || type == SMALL))
			free_block(ptr - sizeof(t_block), zone, type);
		else if (type == LARGE)
			free_zone(ptr - sizeof(t_zone), &g_mem.large, &g_mem.large_end);
	}
}
