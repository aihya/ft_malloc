/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 12:51:06 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 17:15:57 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putaddr(void *addr, int prefix, int newline)
{
	if (prefix)
		ft_putstr("0x");
	ft_putnbr_base((unsigned long long)addr, 16);
	if (newline)
		ft_putchar('\n');
}
