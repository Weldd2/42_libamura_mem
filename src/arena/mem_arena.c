/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:14:22 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/13 20:11:49 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

t_mem_arena_block	**mem_arena_head(void)
{
	static t_mem_arena_block	*head = NULL;

	if (!head)
	{
		head = malloc(sizeof(t_mem_arena_block));
		if (!head)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		head->block = malloc(ARENA_BLOC_SIZE);
		if (!head->block)
		{
			perror("malloc");
			free(head);
			exit(EXIT_FAILURE);
		}
		head->next = NULL;
	}
	return (&head);
}

void	mem_arena_add_block(t_mem_arena_block **arena, size_t size)
{
	size_t				block_size;
	t_mem_arena_block	*new_block;

	if (size == 0)
		return ;
	block_size = ARENA_BLOC_SIZE;
	while (size > block_size)
		block_size *= 2;
	new_block = malloc(sizeof(t_mem_arena_block));
	if (!new_block)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_block->block = malloc(block_size);
	if (!new_block->block)
	{
		perror("malloc");
		free(new_block);
		exit(EXIT_FAILURE);
	}
	new_block->next = *arena;
	*arena = new_block;
}
