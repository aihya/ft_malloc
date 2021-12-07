/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 11:18:26 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 17:13:33 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <pthread.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <unistd.h>
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>

# define NUM_BLOCKS	128
# define TRUE		1
# define FALSE		0
# define TINY		1
# define SMALL		2
# define LARGE		3

# define FIX_RESET

typedef struct s_block
{
	struct s_block	*next;
	size_t			size;
	short			free;
}					t_block;

typedef struct s_zone
{
	struct s_zone	*next;
	struct s_zone	*prev;
	size_t			size;
}					t_zone;

typedef struct s_mem
{
	t_zone		*tiny;
	t_zone		*small;
	t_zone		*large;
	t_zone		*tiny_end;
	t_zone		*small_end;
	t_zone		*large_end;
	size_t		tzs;
	size_t		tbs;
	size_t		szs;
	size_t		sbs;
}				t_mem;

t_mem			g_mem;
pthread_mutex_t	g_mutex;

//		Large
void	*alloc_large(size_t size);

//		Tiny and Small
void	*alloc_block(size_t size, int type);

//		Zone
void	*shift_zone(t_zone *zone);
t_zone	*new_zone(size_t size, int type);

//		Memory mapping
void	*mem_alloc(size_t size);

//		malloc
void	*malloc(size_t size);
void	*ft_malloc(size_t size);

//		free
void	free(void *ptr);
void	ft_free(void *ptr, t_zone *hint);
void	free_zone(t_zone *zone, t_zone **head, t_zone **tail);
void	free_block(t_block *block, t_zone *zone, int type);

//		realloc
void	*realloc(void *ptr, size_t size);
void	*ft_realloc(void *ptr, size_t size);

//		calloc
void	*calloc(size_t count, size_t size);
void	*ft_calloc(size_t count, size_t size);

//		Shifting
void	*shift_block(t_block *block);
void	*shift_zone(t_zone *zone);

//		Block allocation
t_block	*split_block(t_block *block, size_t size);

//		Show allocated memory
void	show_alloc_mem(void);
void	show_all(void);

// Search
t_zone	*search_zone(void *ptr, t_zone *head);
t_zone	*search_block(void *ptr, t_zone *head, int *state);
int		search(void *ptr, t_zone **zone, int *type, int *state);

// Health
int     corrupted(t_block *block, t_zone *zone);
int		fix(t_block *block, t_zone *zone);

// Best fit
t_block	*best_fit(size_t size, t_zone *head, int type);

// Defragementation
size_t	defragement(t_zone *zone);
void	defragement_from(t_block *block);

// Consts
void	init_consts(void);

// Tools
int		zone_type(t_zone *zone);
int		block_type(t_block *block);
int		size_type(size_t size);
size_t	min_block_size(int type);
size_t	zone_size(int type);

// Hexdump
void	hexdump(void);

#endif
