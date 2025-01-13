/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_arena.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:48:28 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/13 20:29:49 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_ARENA_H
# define MEM_ARENA_H
# define ARENA_BLOC_SIZE 65536
# include <stdio.h>
# include <stdlib.h>

typedef struct s_mem_arena_block
{
	struct s_mem_arena_block	*next;
	void						*block;
}	t_mem_arena_block;

/**
 * @brief Ajoute un nouveau bloc à l'arène.
 *
 * Cette fonction alloue un nouveau bloc de mémoire de taille adaptée
 * et l'ajoute en tête de la liste des blocs de l'arène.
 *
 * @param arena Pointeur vers la tête de l'arène.
 * @param size Taille de l'allocation demandée.
 */
void				mem_arena_add_block(t_mem_arena_block **arena, size_t size);

/**
 * @brief Obtient le pointeur vers la tête de l'arène.
 *
 * Cette fonction initialise la tête de l'arène si elle n'est pas déjà
 * initialisée et retourne un pointeur vers celle-ci.
 *
 * @return t_mem_arena_block** Pointeur vers la tête de l'arène.
 */
t_mem_arena_block	**mem_arena_head(void);

/**
 * @brief Libère toute la mémoire allouée par l'arène.
 *
 * Cette fonction parcourt tous les blocs de l'arène et les libère,
 * puis réinitialise la tête de l'arène à NULL.
 */
void				mem_arena_free(void);

/**
 * @brief Alloue de la mémoire dans l'arène.
 *
 * Cette fonction alloue un bloc de mémoire de la taille spécifiée
 * à partir de l'arène. Si l'arène n'a pas assez d'espace, un nouveau
 * bloc est ajouté.
 *
 * @param size Taille de la mémoire à allouer.
 * @return void* Pointeur vers la mémoire allouée ou NULL si la taille est zéro.
 */
void				*mem_arena_alloc(size_t size);

/**
 * @brief Alloue de la mémoire et l'initialise à zéro dans l'arène.
 *
 * Cette fonction alloue de la mémoire pour un nombre donné d'éléments de taille
 * spécifiée dans l'arène et initialise la mémoire allouée à zéro.
 *
 * @param nmemb Nombre d'éléments à allouer.
 * @param size Taille de chaque élément.
 * @return void* Pointeur vers la mémoire allouée et initialisée à zéro,
 *                ou NULL si l'allocation échoue.
 */
void				*mem_arena_calloc(size_t nmemb, size_t size);

/**
 * @brief Réalloue un bloc de mémoire dans l'arène.
 *
 * Cette fonction redimensionne un bloc de mémoire précédemment alloué dans
 * l'arène. Si la nouvelle taille est supérieure, elle alloue un nouvel espace
 * et copie les données existantes. Si la nouvelle taille est inférieure, elle
 * réduit simplement la taille enregistrée.
 *
 * @param ptr Pointeur vers la mémoire à redimensionner.
 * @param old_size Ancienne taille.
 * @param new_size Nouvelle taille demandée.
 * @return void* Pointeur vers la mémoire redimensionnée,
 *                ou NULL si l'allocation échoue.
 */
void				*mem_arena_realloc(void *ptr, size_t new_size);

#endif