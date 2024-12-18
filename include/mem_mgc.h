/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:48:09 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/18 23:47:46 by antoinemura      ###   ########.fr       */
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

/**
 * @brief Libère tous les blocs de mémoire gérés par le gestionnaire de mémoire magique.
 *
 * La fonction `mem_mgc_free()` parcourt la liste interne de tous les blocs de mémoire
 * gérés et appelle, pour chaque bloc, la fonction de libération qui lui est associée.
 * Elle libère ensuite la structure interne de suivi, remettant ainsi le gestionnaire de
 * mémoire dans un état vide. Après l'appel à cette fonction, tous les blocs alloués via
 * ce gestionnaire sont considérés comme invalides.
 *
 * @warning
 * - Après l'appel de cette fonction, tous les pointeurs retournés précédemment par le
 *   gestionnaire ne doivent plus être utilisés.
 * - Cette fonction n'est pas thread-safe. Si vous utilisez ce gestionnaire dans un contexte
 *   multi-threadé, protégez l'accès par un mécanisme de synchronisation approprié.
 *
 * @see mem_mgc_alloc(), mem_mgc_calloc(), mem_mgc_head(), mem_mgc_add_block(), mem_mgc_create_block()
 */
void mem_mgc_free();

/**
 * @brief Retourne l'adresse du pointeur vers la tête de la liste interne des blocs gérés.
 *
 * La fonction `mem_mgc_head()` renvoie un double pointeur sur la tête de la liste chaînée
 * interne utilisée par le gestionnaire de mémoire magique. Chaque appel d'allocation ou
 * d'ajout manuel de bloc modifie cette liste.
 *
 * @return t_mem_mgc_block** Un double pointeur vers le premier élément de la liste de blocs gérés.
 *
 * @note Cette fonction est principalement à usage interne pour le gestionnaire de mémoire.
 *       L'utiliser directement nécessite une bonne compréhension du fonctionnement interne.
 *
 * @warning Manipuler la liste en dehors des fonctions fournies peut entraîner des fuites
 *          de mémoire ou des comportements indéfinis.
 *
 * @see mem_mgc_add_block(), mem_mgc_create_block(), mem_mgc_alloc(), mem_mgc_calloc()
 */
t_mem_mgc_block **mem_mgc_head();

/**
 * @brief Ajoute un bloc de mémoire déjà alloué au gestionnaire de mémoire magique.
 *
 * La fonction `mem_mgc_add_block()` prend en paramètre un pointeur vers un bloc de mémoire 
 * déjà alloué par d'autres moyens (par exemple `malloc`), et l'ajoute à la liste interne des 
 * blocs gérés. Une fonction de libération personnalisée peut être spécifiée ; sinon, `free`
 * sera utilisée par défaut. Ainsi, le bloc sera automatiquement libéré lorsque `mem_mgc_free()`
 * sera appelé.
 *
 * @param block Le pointeur vers le bloc de mémoire déjà alloué.
 * @param free_func Un pointeur vers une fonction personnalisée de libération mémoire (de type 
 *                  `void (*)(void *)`). Si `NULL`, la fonction standard `free` sera utilisée.
 *
 * @return void* Le pointeur vers le bloc ajouté, ou `NULL` en cas d'échec.
 *
 * @warning
 * - Ne pas libérer manuellement ce bloc par d'autres moyens après l'avoir ajouté. 
 *   Le gestionnaire s'en occupera lors de `mem_mgc_free()`.
 * - Cette fonction n'est pas thread-safe. En environnement multi-threadé, protégez son
 *   appel par un mutex ou un autre mécanisme de synchronisation.
 *
 * @see mem_mgc_create_block(), mem_mgc_free(), mem_mgc_alloc(), mem_mgc_calloc()
 */
void *mem_mgc_add_block(void *block, void (*free_func)(void *));

/**
 * @brief Alloue un nouveau bloc de mémoire et l'enregistre dans la liste interne des blocs gérés.
 *
 * La fonction `mem_mgc_create_block()` effectue une nouvelle allocation mémoire de la taille 
 * spécifiée et l'ajoute au gestionnaire de mémoire magique, accompagnée d'une fonction de 
 * libération (personnalisée ou `free` par défaut). Le bloc sera ainsi automatiquement libéré 
 * lors de l'appel à `mem_mgc_free()`.
 *
 * @param size La taille, en octets, du bloc de mémoire à allouer.
 * @param free_func Un pointeur vers une fonction personnalisée de libération mémoire (de type
 *                  `void (*)(void *)`). Si `NULL`, la fonction standard `free` sera utilisée.
 *
 * @return void* Un pointeur vers le bloc de mémoire nouvellement alloué.
 *
 * @exception En cas d'échec d'allocation (du bloc ou de la structure interne), la fonction 
 *            appelle `exit(EXIT_FAILURE)` et termine le programme.
 *
 * @warning
 * - Cette fonction n'est pas thread-safe.
 * - En cas d'échec d'allocation, le programme s'arrêtera.
 *
 * @see mem_mgc_add_block(), mem_mgc_free(), mem_mgc_alloc(), mem_mgc_calloc()
 */
void *mem_mgc_create_block(size_t size, void (*free_func)(void *));

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