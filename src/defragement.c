/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defregement.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 16:29:43 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 16:30:08 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	defragement_from(t_block *block)
{
	t_block	*curr;

	curr = block;
	while (curr && curr->free)
	{
		if (curr->next && curr->next->free)
		{
			curr->size += curr->next->size;
			curr->next = curr->next->next;
		}
		curr = curr->next;
	}
}

size_t	defragement(t_zone *zone)
{
	t_block	*block;
	size_t	total;

	total = 0;
	block = (t_block *)shift_zone(zone);
	while (block)
	{
		if (block->free)
		{
			while (block->next && block->next->free)
			{
				block->size += block->next->size;
				block->next = block->next->next;
			}
			total += block->size;
		}
		block = block->next;
	}
	return (total);
}
