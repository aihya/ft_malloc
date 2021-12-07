/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:17:39 by aihya             #+#    #+#             */
/*   Updated: 2021/12/07 18:15:56 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int     main()
{
	char *str;
	int i;

	str = (char *)malloc(10000);
	// i = 0;
	// while (i < 500)
	// {
	// 	if (str[i] == 0)
	// 		printf(".");
	// 	else
	// 		printf("-");
	// 	i++;
	// }
	// printf("\n");
	// show_all();
	// hexdump();

	// i = 0;
	// while (i < 500)
	// {
	// 	// str1[i] = (char *)malloc(10);
	// 	str[i] = (char *)malloc(i+1);

	// 	// show_all();
	// 	// int j = 0;
	// 	// while (j < i+2)
	// 	// {
	// 	//     str1[i][j] = 42;
	// 	//     j++;
	// 	// }
	// 	// str1[i][j] = 0;
	// 	// printf("%s\n", str1[i]);
	// 	i++;
	// }
	// ft_memset(str[0], 1, 2);
	// realloc(str[1], 100);
	// malloc(10);
	// malloc(123);
	// i = 0;
	// while (i < 1000)
	// {
	// 	if ((i+1) % 2)
	// 		free(str[i]);
	// 	i++;
	// }
	// malloc(1024);
	// i = 0;
	// while (i < 1024)
	// {
	//     if (i % 2)
	//         free(str1[i]);
	//     i++;
	// }

	// show_mem();
	// show_alloc_mem();
	// i = 0;
	// while (i < 10)
	// {
	//     free(str1[i]);
	//     i++;
	// }
	// show_alloc_mem();
  
	return (0);
}

//TODO: Add fix_health for free and realloc