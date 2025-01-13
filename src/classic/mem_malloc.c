/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_malloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 23:09:20 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/13 20:14:55 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*mem_malloc(size_t size)
{
	t_mem_header	*header;
	size_t			total_size;

	total_size = sizeof(t_mem_header) + size;
	header = malloc(total_size);
	if (!header)
		return (NULL);
	header->size = size;
	return ((void *)(header + 1));
}
