/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_calloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:13:32 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/09 23:41:55 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*mem_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
		return (mem_malloc(0));
	ptr = mem_malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	mem_memset(ptr, 0, nmemb * size);
	return (ptr);
}
