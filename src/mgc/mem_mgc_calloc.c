/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgc_calloc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:35:11 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/18 22:23:12 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*mem_mgc_calloc(size_t nmemb, size_t size, ... )
{
	va_list	args;
	void	(*free_func)(void *);
	void	*ptr;

	va_start(args, size);
	free_func = va_arg(args, void (*)(void *));
	va_end(args);
	if (free_func == NULL)
		free_func = free;
	ptr = mem_mgc_alloc(nmemb * size, free_func);
	if (ptr)
		mem_memset(ptr, 0, nmemb * size);
	return (ptr);
}
