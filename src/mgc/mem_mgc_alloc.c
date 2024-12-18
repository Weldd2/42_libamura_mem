/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgc_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:47:28 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/18 21:31:30 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*mem_mgc_alloc(size_t size, ... )
{
	va_list					args;
	void					(*free_func)(void *);

	if (size == 0)
		return (NULL);
	va_start(args, size);
	free_func = handle_mgc_args(size, args);
	va_end(args);
	return (mem_mgc_add_block(size, free_func));
}