/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:18:21 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/18 23:43:02 by antoinemura      ###   ########.fr       */
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

void	*mem_mgc_create_block(size_t size, void (*free_func)(void *))
{
	t_mem_mgc_block	*new;
	t_mem_mgc_block	**head;

	head = mem_mgc_head();
	new = malloc(sizeof(t_mem_mgc_block));
	if (!new)
		exit(EXIT_FAILURE);
	new->block = malloc(size);
	if (!new->block)
	{
		free(new);
		exit(EXIT_FAILURE);
	}
	new->free_func = free_func;
	new->next = NULL;
	lstadd_front(head, new);
	return ((*head)->block);
}

void	*mem_mgc_add_block(void *block, void (*free_func)(void *))
{
	t_mem_mgc_block	*new;
	t_mem_mgc_block	**head;

	head = mem_mgc_head();
	new = malloc(sizeof(t_mem_mgc_block));
	if (!new)
		exit(EXIT_FAILURE);
	new->block = block;
	if (!new->block)
	{
		free(new);
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
