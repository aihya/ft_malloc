/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:27:54 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 18:55:08 by aihya            ###   ########.fr       */
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
	else if (block->size - sizeof(t_block) > size)
		return (attempt_split(block, type, size));
	else if (block->size - sizeof(t_block) < size)
	{
		if (block->next && block->next->free)
			return (attempt_merge(block, type, size));
	}
	return (NULL);
}
