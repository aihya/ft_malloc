/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:26:11 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 18:55:33 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	show_zones(t_zone *head, int type, size_t *bytes, int all)
{
	t_zone	*zone;

	zone = head;
	while (zone)
	{
		print_header(zone, type);
		if (type == TINY || type == SMALL)
			print_blocks(zone, bytes, all);
		else
			print_large(zone, bytes);
		zone = zone->next;
	}
}

void	show_all(void)
{
	size_t	bytes;

	bytes = 0;
	show_zones(g_mem.tiny, TINY, &bytes, TRUE);
	show_zones(g_mem.small, SMALL, &bytes, TRUE);
	show_zones(g_mem.large, LARGE, &bytes, TRUE);
	ft_putstr("Total : ");
	ft_putnbr(bytes);
	ft_putstr(" bytes\n");
}

void	show_alloc_mem(void)
{
	size_t	bytes;

	bytes = 0;
	show_zones(g_mem.tiny, TINY, &bytes, FALSE);
	show_zones(g_mem.small, SMALL, &bytes, FALSE);
	show_zones(g_mem.large, LARGE, &bytes, FALSE);
	ft_putstr("Total : ");
	ft_putnbr(bytes);
	ft_putstr(" bytes\n");
}
