/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgc_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:58:41 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/13 20:15:58 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	mem_mgc_free(void)
{
	t_mem_mgc_block	**head;
	t_mem_mgc_block	*current;
	t_mem_mgc_block	*tmp;

	head = mem_mgc_head();
	current = *head;
	while (current)
	{
		tmp = current->next;
		if (current->block != NULL)
			current->free_func(current->block);
		mem_free(current);
		current = tmp;
	}
	*head = NULL;
}
