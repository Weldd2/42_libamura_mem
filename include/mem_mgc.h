/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:48:09 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/18 21:29:42 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_MGC_H
# define MEM_MGC_H
# include <stdio.h>

typedef struct s_mem_mgc_block
{
	struct s_mem_mgc_block	*next;
	void					*block;
	void					(*free_func)(void *);
}	t_mem_mgc_block;

t_mem_mgc_block	*mem_mgc_head();

t_mem_mgc_block	*mem_mgc_add_block(size_t size, void (*free_func)(void *));

void			(*handle_mgc_args(size_t size, ...))(void *);

/**
 * @brief Alloue de la mémoire avec gestion automatique (gestionnaire de mémoire magique).
 *
 * La fonction `mem_mgc_alloc` alloue un bloc de mémoire de la taille spécifiée et l'enregistre
 * auprès du gestionnaire de mémoire magique. La mémoire allouée sera automatiquement libérée
 * lorsque le gestionnaire de mémoire sera vidé, ce qui aide à prévenir les fuites de mémoire.
 *
 * @param size La taille (en octets) du bloc de mémoire à allouer.
 * @param ... Arguments variables optionnels :
 *            - Un pointeur vers une fonction de libération personnalisée de type `void (*)(void *)`.
 *              Si aucune fonction n'est fournie ou si le pointeur est `NULL`, la fonction
 *              standard `free` sera utilisée par défaut.
 *
 * @return void* Un pointeur vers le bloc de mémoire alloué, ou `NULL` si :
 *               - La taille demandée est zéro.
 *               - L'allocation de mémoire échoue.
 *               - L'allocation d'un nouveau bloc de gestion échoue.
 *
 * @details
 * Cette fonction facilite la gestion de la mémoire en enregistrant chaque bloc alloué
 * dans une liste interne. Chaque bloc est associé à une fonction de libération qui sera
 * appelée lors de la libération de toute la mémoire gérée. Cela permet de centraliser
 * la gestion des libérations de mémoire et de réduire le risque de fuites mémorielles.
 *
 * **Utilisation :**
 * ```c
 * #include "mem.h"
 *
 * void custom_free(void *ptr)
 * {
 *     // Implémentation personnalisée de la libération de mémoire
 *     free(ptr);
 * }
 *
 * int main(void)
 * {
 *     // Allocation avec la fonction de libération par défaut (`free`)
 *     int *numbers = mem_mgc_alloc(10 * sizeof(int), NULL);
 *
 *     // Allocation avec une fonction de libération personnalisée
 *     char *buffer = mem_mgc_alloc(256, custom_free);
 *
 *     // Utilisation des blocs alloués...
 *
 *     // Libération de tous les blocs alloués par le gestionnaire de mémoire magique
 *     mem_mgc_free_all();
 *
 *     return 0;
 * }
 * ```
 *
 * @warning
 * - Assurez-vous d'appeler `mem_mgc_free_all()` avant la fin de votre programme pour libérer
 *   toutes les mémoires allouées et éviter les fuites.
 * - Cette fonction n'est pas thread-safe. Si votre application est multi-threadée, vous devez
 *   protéger les appels à `mem_mgc_alloc` avec des mécanismes de synchronisation appropriés.
 *
 * @see mem_mgc_free_all()
 */
void	*mem_mgc_alloc(size_t size, ... );

/**
 * @brief Alloue de la mémoire et l'initialise à zéro avec gestion automatique.
 *
 * @param nmemb Nombre d'éléments à allouer.
 * @param size Taille de chaque élément en octets.
 * @param ... Arguments variables optionnels :
 *            - Un pointeur vers une fonction de libération personnalisée de type `void (*)(void *)`.
 *              Si aucune fonction n'est fournie ou si le pointeur est `NULL`, la fonction
 *              standard `free` sera utilisée par défaut.
 *
 * @return void* Un pointeur vers la mémoire allouée et initialisée à zéro, ou `NULL` si :
 *               - Le produit `nmemb * size` est zéro.
 *               - L'allocation de mémoire échoue.
 *               - L'allocation d'un nouveau bloc de gestion échoue.
 */
void	*mem_mgc_calloc(size_t nmemb, size_t size, ... );

#endif