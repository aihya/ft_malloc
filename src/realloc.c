/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:40:47 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 19:10:42 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*realloc_large(t_zone *zone, size_t size)
{
	size_t	max;

	max = zone->size - sizeof(t_zone);
	if (max > size)
		max = size;
	return (replace(shift_zone(zone), zone, size, max));
}

void	*realloc_block(t_block *block, t_zone *zone, int type, size_t size)
{
	t_block	*new;
	size_t	max;

	max = block->size - sizeof(t_block);
	if (max > size)
		max = size;
	if (size_type(size) == type)
	{
		new = shift_block(resize_block(block, type, size));
		if (new == NULL)
			new = replace(shift_block(block), zone, size, max);
		return (new);
	}
	return (replace(shift_block(block), zone, size, max));
}

void	*ft_realloc(void *ptr, size_t size)
{
	struct rlimit	rlim;
	t_zone			*zone;
	int				type;
	int				isfree;

	init_consts();
	getrlimit(RLIMIT_DATA, &rlim);
	if (size == 0 || size > rlim.rlim_cur)
		return (NULL);
	if (ptr == NULL)
		return (ft_malloc(size));
	zone = NULL;
	type = -1;
	isfree = TRUE;
	if (search(ptr, &zone, &type, &isfree))
	{
		if (!isfree && (type == TINY || type == SMALL))
			return (realloc_block(ptr - sizeof(t_block), zone, type, size));
		else if (type == LARGE)
			return (realloc_large(ptr - sizeof(t_zone), size));
	}
	return (ptr);
}
