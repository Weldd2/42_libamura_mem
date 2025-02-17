/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgc_calloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:35:11 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/13 16:14:02 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*mem_mgc_calloc(size_t nmemb, size_t size, void (*free_func)(void *))
{
	void	*ptr;

	if (free_func == NULL)
		free_func = mem_free;
	ptr = mem_mgc_alloc(nmemb * size, free_func);
	if (ptr)
		mem_memset(ptr, 0, nmemb * size);
	return (ptr);
}
