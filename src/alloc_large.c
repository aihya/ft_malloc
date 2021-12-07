/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_large.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 17:36:40 by aihya             #+#    #+#             */
/*   Updated: 2021/12/06 15:53:50 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *alloc_large(size_t size)
{
	t_zone	*zone;

	zone = new_zone(size, LARGE);
	if (zone == NULL)
		return (NULL);
	if (g_mem.large == NULL)
	{
		g_mem.large = zone;
		g_mem.large_end = zone;
	}
	else
	{
		g_mem.large_end->next = zone;
		g_mem.large_end->next->prev = g_mem.large_end;
		g_mem.large_end = g_mem.large_end->next;
	}
	return (shift_zone(zone));
}