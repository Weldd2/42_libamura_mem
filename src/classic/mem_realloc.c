/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:13:06 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/11 16:16:03 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*mem_realloc(void *ptr, size_t size)
{
	t_mem_header	*header;
	void			*new_ptr;
	size_t			old_size;
	size_t			size_to_cpy;

	if (!ptr)
		return (mem_malloc(size));
	header = (t_mem_header*)ptr - 1;
	old_size = header->size;
	new_ptr = mem_malloc(size);
	if (!new_ptr)
		return (NULL);
	size_to_cpy = old_size;
	if (old_size > size)
		size_to_cpy = size;
	mem_memcpy(new_ptr, ptr, size_to_cpy);
	mem_free(ptr);
	return (new_ptr);
}
