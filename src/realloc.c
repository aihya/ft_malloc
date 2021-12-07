/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:40:47 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 16:38:49 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*replace(void *ptr, t_zone *hint, size_t size, size_t max)
{
	void	*new;

	new = ft_malloc(size);
	if (new)
	{
		ft_memcpy(new, ptr, max);
		ft_free(ptr, hint);
	}
	return (new);
}

static t_block	*attempt_split(t_block *block, int type, size_t size)
{
	if (block->size - (size + sizeof(t_block)) >= min_block_size(type))
	{
		split_block(block, size + sizeof(t_block));
		defragement_from(block->next);
		return (block);
	}
	return (NULL);
}

static t_block	*attempt_merge(t_block *block, int type, size_t size)
{
	size_t	merge_size;

	merge_size = block->size + block->next->size;
	if (merge_size >= size + sizeof(t_block))
	{
		if (merge_size - (size + sizeof(t_block)) >= min_block_size(type))
		{
			block->size = merge_size;
			block->next = block->next->next;
			split_block(block, size + sizeof(t_block));
			defragement_from(block->next);
			return (block);
		}
	}
	return (NULL);
}

t_block	*resize_block(t_block *block, int type, size_t size)
{
	if (block->size - sizeof(t_block) == size)
		return (block);
	else if (block->size - sizeof(t_block) > size) // Shrink block
		return (attempt_split(block, type, size));
	else if (block->size - sizeof(t_block) < size) // Extend block
	{
		if (block->next && block->next->free)
			return (attempt_merge(block, type, size));
	}
	return (NULL);
}

void	*realloc_large(t_zone *zone, size_t size)
{
	size_t	max;

	max = zone->size - sizeof(t_zone);
	if (max > size)
		max = size;
	return (replace(shift_zone(zone), zone, size, max));
}

void    *realloc_block(t_block *block, t_zone *zone, int type, size_t size)
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

void    *ft_realloc(void *ptr, size_t size)
{
	struct rlimit	rlim;
	t_zone			*zone;
	int				type;
	int				isfree;

	init_consts();
	getrlimit(RLIMIT_DATA, &rlim);
	if (size == 0 || size > rlim.rlim_cur)
		return (ptr);
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