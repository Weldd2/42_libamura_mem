/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_arena_realloc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:14:22 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/18 20:31:21 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*mem_arena_realloc(void *ptr, size_t new_size)
{
	void	*new;

	new = mem_arena_alloc(new_size);
	mem_memcpy(ptr, new, new_size);
	return (new);
}
