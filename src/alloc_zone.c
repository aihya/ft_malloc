/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_zone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:06:33 by aihya             #+#    #+#             */
/*   Updated: 2021/12/03 10:09:19 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	*memmap(size_t size)
{
	static int	prot = PROT_READ | PROT_WRITE;
	static int	flag = MAP_PRIVATE | MAP_ANONYMOUS;

	return (mmap(NULL, size, prot, flag, -1, 0));
}

t_zone	*new_zone(size_t size, int type)
{
	t_zone	*zone;
	t_block	*block;

	zone = (t_zone *)memmap(size);
	if (zone != MAP_FAILED)
	{
		zone->next = NULL;
		zone->prev = NULL;
		zone->size = size;
		if (type != LARGE)
		{
			block = (t_block *)shift_zone(zone);
			block->size = zone->size - sizeof(t_zone);
			block->free = TRUE;
			block->next = NULL;
		}
	}
	return (zone);
}
