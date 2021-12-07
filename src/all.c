/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 11:02:55 by aihya             #+#    #+#             */
/*   Updated: 2021/12/06 18:40:01 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

pthread_mutex_t	g_mutex = PTHREAD_MUTEX_INITIALIZER;

void	*malloc(size_t size)
{
	void	*ptr;

	ptr = NULL;
	pthread_mutex_lock(&g_mutex);
	ptr = ft_malloc(size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void	*realloc(void *ptr, size_t size)
{
	pthread_mutex_lock(&g_mutex);
	ptr = ft_realloc(ptr, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}

void	free(void *ptr)
{
	pthread_mutex_lock(&g_mutex);
	ft_free(ptr, NULL);
	pthread_mutex_unlock(&g_mutex);
}

void	*calloc(size_t count, size_t size)
{
	void	*ptr;

	pthread_mutex_lock(&g_mutex);
	ptr = ft_calloc(count, size);
	pthread_mutex_unlock(&g_mutex);
	return (ptr);
}
