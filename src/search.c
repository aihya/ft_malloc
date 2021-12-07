/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 13:45:33 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 16:27:56 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_zone	*search_block(void *ptr, t_zone *head, int *state)
{
	t_zone	*zone;
	t_block	*block;

	zone = head;
	while (zone)
	{
		if (ptr - sizeof(t_block) >= shift_zone(zone)
			&& ptr - sizeof(t_block) < (void *)zone + zone->size)
		{
			block = (t_block *)shift_zone(zone);
			while (block)
			{
				if ((void *)block == ptr - sizeof(t_block))
				{
					*state = block->free;
					return (zone);
				}
				block = block->next;
			}
		}
		zone = zone->next;
	}
	return (NULL);
}

t_zone	*search_zone(void *ptr, t_zone *head)
{
	t_zone	*zone;

	zone = head;
	while (zone)
	{
		if ((void *)zone == ptr - sizeof(t_zone))
			break;
		zone = zone->next;
	}
	return (zone);
}

int		search(void *ptr, t_zone **zone, int *type, int *state)
{
	*zone = NULL;
	*zone = search_block(ptr, g_mem.tiny, state);
	if (*zone)
	{
		*type = TINY;
		return (TRUE);
	}
	*zone = search_block(ptr, g_mem.small, state);
	if (*zone)
	{
		*type = SMALL;
		return (TRUE);
	}
	*zone = search_zone(ptr, g_mem.large);
	if (*zone)
	{
		*type = LARGE;
		return (TRUE);
	}
	return (FALSE);
}