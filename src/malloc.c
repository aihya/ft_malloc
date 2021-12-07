/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:59:58 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 18:26:13 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*ft_malloc(size_t size)
{
	struct rlimit	rlim;

	init_consts();
	getrlimit(RLIMIT_DATA, &rlim);
	if (size == 0 || size > rlim.rlim_cur)
		return (NULL);
	if (size_type(size) == TINY)
		return (alloc_block(size + sizeof(t_block), TINY));
	if (size_type(size) == SMALL)
		return (alloc_block(size + sizeof(t_block), SMALL));
	return (alloc_large(size + sizeof(t_zone)));
}
