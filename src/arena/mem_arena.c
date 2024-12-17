/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:14:22 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/17 18:15:06 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

/**
 * @brief Obtient le pointeur vers la tête de l'arène.
 *
 * Cette fonction initialise la tête de l'arène si elle n'est pas déjà
 * initialisée et retourne un pointeur vers celle-ci.
 *
 * @return t_arena_mem_block_list** Pointeur vers la tête de l'arène.
 */
static t_arena_mem_block_list	**mem_arena_head(void)
{
	static t_arena_mem_block_list	*head = NULL;

	if (!head)
	{
		head = malloc(sizeof(t_arena_mem_block_list));
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

/**
 * @brief Ajoute un nouveau bloc à l'arène.
 *
 * Cette fonction alloue un nouveau bloc de mémoire de taille adaptée
 * et l'ajoute en tête de la liste des blocs de l'arène.
 *
 * @param arena Pointeur vers la tête de l'arène.
 * @param size Taille de l'allocation demandée.
 */
void	mem_add_block(t_arena_mem_block_list **arena, size_t size)
{
	size_t					block_size;
	t_arena_mem_block_list	*new_block;

	if (size == 0)
		return ;
	block_size = ARENA_BLOC_SIZE;
	while (size > block_size)
		block_size *= 2;
	new_block = malloc(sizeof(t_arena_mem_block_list));
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

void	mem_free_arena(void)
{
	t_arena_mem_block_list	**arena;
	t_arena_mem_block_list	*temp;
	t_arena_mem_block_list	*next;

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

void	*mem_arena_alloc(size_t size)
{
	t_arena_mem_block_list	**arena;
	static size_t			pos = 0;

	if (size == 0)
		return (NULL);
	arena = mem_arena_head();
	if ((*arena) == NULL)
		return (NULL);
	if (size + pos > ARENA_BLOC_SIZE)
	{
		mem_add_block(arena, size);
		pos = 0;
	}
	pos += size;
	return ((char *)(*arena)->block + (pos - size));
}
