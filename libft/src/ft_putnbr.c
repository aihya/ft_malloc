/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/12 16:07:24 by aihya             #+#    #+#             */
/*   Updated: 2021/09/17 15:51:34 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_base(unsigned long long n, unsigned int base)
{
	int		i;
	char	buffer[50];

	if (base)
	{
		i = 0;
		while (1337)
		{
			buffer[i++] = HEX_CHARS[n % base];
			n /= base;
			if (!n)
				break ;
		}
		while (i)
			ft_putchar(buffer[--i]);
	}
}

void	ft_putnbr(long long n)
{
	if (n < 0)
	{
		ft_putchar('-');
		if (n == LLONG_MIN)
		{
			n = (n / 10) * (-1);
			ft_putnbr(n);
			ft_putchar(-(LLONG_MIN % 10) + 48);
			return ;
		}
		n *= -1;
	}
	ft_putnbr_base(n, 10);
}
