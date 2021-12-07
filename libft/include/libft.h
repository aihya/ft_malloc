/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:42:58 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 17:16:15 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <limits.h>

# define HEX_CHARS	"0123456789ABCDEF"

void	ft_putaddr(void *addr, int prefix, int newline);
void	ft_putnbr(long long n);
void	ft_putchar(char c);
void	ft_putendl(char const *s);
void	ft_putstr(char const *s);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	ft_putnbr_base(unsigned long long n, unsigned int base);

#endif
