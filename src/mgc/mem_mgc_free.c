/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgc_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:58:41 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/18 23:25:22 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	mem_mgc_free()
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
		free(current);
		current = tmp;
	}
	*head = NULL;
}
