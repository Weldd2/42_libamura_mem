/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_arena_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:57:27 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/13 20:12:10 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	mem_arena_free(void)
{
	t_mem_arena_block	**arena;
	t_mem_arena_block	*temp;
	t_mem_arena_block	*next;

	arena = mem_arena_head();
	if (*arena == NULL)
		return ;
	temp = *arena;
	while (temp != NULL)
	{
		next = temp->next;
		free(temp->block);
		free(temp);
		temp = next;
	}
	*arena = NULL;
}
