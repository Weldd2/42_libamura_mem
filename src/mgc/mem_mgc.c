/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:18:21 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/13 16:13:49 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include <stdarg.h>
#include <stdlib.h>

void	lstadd_front(t_mem_mgc_block **lst, t_mem_mgc_block *new)
{
	if (lst == NULL || new == NULL)
		return;
	new->next = *lst;
	*lst = new;
}

void	*mem_mgc_add_block(void *block, void (*free_func)(void *))
{
	t_mem_mgc_block	*new;
	t_mem_mgc_block	**head;

	head = mem_mgc_head();
	new = mem_malloc(sizeof(t_mem_mgc_block));
	if (!new)
		exit(EXIT_FAILURE);
	new->block = block;
	if (!new->block)
	{
		mem_free(new);
		exit(EXIT_FAILURE);
	}
	new->free_func = free_func;
	new->next = NULL;
	lstadd_front(head, new);
	return ((*head)->block);
}

t_mem_mgc_block	**mem_mgc_head()
{
	static t_mem_mgc_block	*head = NULL;

	return (&head);
}
