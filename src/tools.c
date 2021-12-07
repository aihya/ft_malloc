/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 11:49:22 by aihya             #+#    #+#             */
/*   Updated: 2021/12/06 19:09:55 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*shift_zone(t_zone *zone)
{
	if (zone)
		return ((void *)zone + sizeof(t_zone));
	return (NULL);
}

void	*shift_block(t_block *block)
{
	if (block)
		return ((void *)block + sizeof(t_block));
	return (NULL);
}

int	size_type(size_t size)
{
	if (size > g_mem.sbs - sizeof(t_block))
		return (LARGE);
	if (size > g_mem.tbs - sizeof(t_block))
		return (SMALL);
	return (TINY);
}

int	zone_type(t_zone *zone)
{
	if (zone->size == g_mem.szs)
		return (SMALL);
	if (zone->size == g_mem.tzs)
		return (TINY);
	return (LARGE);
}

size_t	min_block_size(int type)
{
	if (type == TINY)
		return (sizeof(t_block) + 1);
	return (g_mem.tbs + 1);
}

size_t	zone_size(int type)
{
	if (type == TINY)
		return (g_mem.tzs);
	return (g_mem.szs);
}

void	init_consts(void)
{
	if (!g_mem.tzs || !g_mem.szs)
	{
		g_mem.tzs = 16 * getpagesize();
		g_mem.szs = 64 * getpagesize();
		g_mem.tbs = g_mem.tzs / NUM_BLOCKS;
		g_mem.sbs = g_mem.szs / NUM_BLOCKS;
	}
}
