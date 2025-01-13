/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_arena_calloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 17:41:05 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/13 20:11:16 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*mem_arena_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (NULL);
	total_size = nmemb * size;
	ptr = mem_arena_alloc(total_size);
	if (ptr)
	{
		mem_memset(ptr, 0, total_size);
	}
	return (ptr);
}
