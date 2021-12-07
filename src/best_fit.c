/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_fit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 18:28:43 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 18:31:20 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static t_block	*__candidate(size_t size, t_zone *zone, size_t min_size)
{
	t_block	*best;
	t_block	*block;

	best = NULL;
	block = (t_block *)shift_zone(zone);
	while (block)
	{
		if (corrupted(block, zone))
		{
			if (fix(block, zone) == FALSE)
				return (NULL);
		}
		if (block->free)
		{
			if (block->size == size)
				return (block);
			if (block->size > size && block->size - size >= min_size)
			{
				if (best == NULL || block->size < best->size)
					best = block;
			}
		}
		block = block->next;
	}
	return (best);
}

t_block	*best_fit(size_t size, t_zone *head, int type)
{
	t_block	*best;
	t_block	*cand;
	t_zone	*zone;
	size_t	min_size;

	min_size = min_block_size(type);
	best = NULL;
	zone = head;
	while (zone)
	{
		cand = __candidate(size, zone, min_size);
		if (cand && cand->size == size)
			return (cand);
		if (cand && (best == NULL || cand->size < best->size))
			best = cand;
		zone = zone->next;
	}
	return (best);
}
