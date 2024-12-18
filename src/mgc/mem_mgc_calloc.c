/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgc_calloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:35:11 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/18 21:30:38 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*mem_mgc_calloc(size_t nmemb, size_t size, ... )
{
	va_list	args;
	void	(*free_func)(void *);
	void	*ptr;

	size_t	total_size = nmemb * size;
	va_start(args, size);
	free_func = handle_mgc_args(size, args);
	va_end(args);
	ptr = mem_mgc_alloc(total_size, free_func);
	if (ptr)
		mem_memset(ptr, 0, total_size);
	return (ptr);
}
