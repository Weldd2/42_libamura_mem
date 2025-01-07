/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgc_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:47:28 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/07 11:58:23 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*mem_mgc_alloc(size_t size, void (*free_func)(void *))
{
	void	*block;

	if (size == 0)
		return (NULL);
	if (free_func == NULL)
		free_func = free;
	block = malloc(size);
	if (!block)
		exit(EXIT_FAILURE);
	return (mem_mgc_add_block(block, free_func));
}
