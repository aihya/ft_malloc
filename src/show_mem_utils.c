/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mem_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:33:06 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 18:33:29 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	print_header(t_zone *zone, int type)
{
	if (type == TINY)
		ft_putstr("TINY : ");
	else if (type == SMALL)
		ft_putstr("SMALL : ");
	else
		ft_putstr("LARGE : ");
	ft_putaddr((void *)zone, TRUE, TRUE);
}

void	print_blocks(t_zone *zone, size_t *bytes, int all)
{
	t_block	*block;

	block = (t_block *)shift_zone(zone);
	while (block)
	{
		if (corrupted(block, zone))
		{
			printf("\x1b[31m*** Corrupted segment: %p\x1b[0m\n", shift_block(block));
			break ;
		}
		else if (all || block->free == FALSE)
		{
			ft_putaddr(shift_block(block), TRUE, FALSE);
			ft_putstr(" - ");
			ft_putaddr((void *)block + block->size, TRUE, FALSE);
			ft_putstr(" : ");
			ft_putnbr(block->size - sizeof(t_block));
			ft_putstr(" bytes");
			if (all && block->free)
				ft_putstr(" free");
			ft_putchar('\n');
			*bytes += block->size - sizeof(t_block);
		}
		block = block->next;
	}
}

void	print_large(t_zone *zone, size_t *bytes)
{
	ft_putaddr(shift_zone(zone), TRUE, FALSE);
	ft_putstr(" - ");
	ft_putaddr((void *)zone + zone->size, TRUE, FALSE);
	ft_putstr(" : ");
	ft_putnbr(zone->size - sizeof(t_zone));
	ft_putendl(" bytes");
	*bytes += zone->size - sizeof(t_zone);
}
