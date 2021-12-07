/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 18:42:43 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 19:11:03 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void    *ft_reallocf(void *ptr, size_t size)
{
    void    *new;

    new = ft_realloc(ptr, size);
    if (new == NULL && ptr)
        ft_free(ptr, NULL);
    return (new);
}
