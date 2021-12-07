/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corruption.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 14:35:48 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 16:50:36 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int	corrupted(t_block *block, t_zone *zone)
{
	if (block->size <= 0)
		return (TRUE);
	if ((void *)block > (void *)zone + zone->size
		|| (void *)block < shift_zone(zone))
		return (TRUE);
	if (block->next != NULL && ((void *)block->next > (void *)zone + zone->size
			|| (void *)block->next < shift_zone(zone)))
		return (TRUE);
	return (FALSE);
}

# if defined (FIX_RESET)

int	fix(t_block *block, t_zone *zone)
{
	block->free = TRUE;
	block->next = NULL;
	block->size = ((void *)zone + zone->size) - ((void *)block);
	return (TRUE);
}

# else

int	fix(t_block *block, t_zone *zone)
{
	(void)block;
	(void)zone;
	return (FALSE);
}

# endif