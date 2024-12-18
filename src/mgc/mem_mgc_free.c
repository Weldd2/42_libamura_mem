/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgc_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:58:41 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/18 21:31:05 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	mem_mgc_free()
{
	t_mem_mgc_block	*current;
	t_mem_mgc_block	*tmp;

	current = mem_mgc_head();
	while (current)
	{
		tmp = current->next;
		if (current->block != NULL)
			current->free_func(current->block);
		current = tmp->next;
	}
}
