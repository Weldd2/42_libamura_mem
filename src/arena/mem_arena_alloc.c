/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_arena_alloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:55:53 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/18 21:32:13 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*mem_arena_alloc(size_t size)
{
	t_mem_arena_block	**arena;
	static size_t			pos = 0;

	if (size == 0)
		return (NULL);
	arena = mem_arena_head();
	if ((*arena) == NULL)
		return (NULL);
	if (size + pos > ARENA_BLOC_SIZE)
	{
		mem_arena_add_block(arena, size);
		pos = 0;
	}
	pos += size;
	return ((char *)(*arena)->block + (pos - size));
}
