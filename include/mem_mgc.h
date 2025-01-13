/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_mgc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:48:09 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/13 20:24:40 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_MGC_H
# define MEM_MGC_H
# include <stdio.h>
# include <stdlib.h>

typedef struct s_mem_mgc_block
{
	struct s_mem_mgc_block	*next;
	void					*block;
	void					(*free_func)(void *);
}	t_mem_mgc_block;

/**
 * @brief Frees all memory blocks managed by the memory manager.
 *
 * The `mem_mgc_free()` function traverses the internal list of all managed 
 * memory blocks and calls the associated free function for each block. It then 
 * frees the internal tracking structures, resetting the memory manager to an 
 * empty state. After calling this function, all memory blocks allocated via 
 * this manager are considered invalid.
 *
 * @warning
 * - After calling this function, all pointers previously returned by the 
 *   manager must no longer be used.
 * - This function is not thread-safe. If you use this manager in a 
 *   multi-threaded context, protect access with an appropriate synchronization 
 *   mechanism.
 *
 * @see mem_mgc_alloc(), mem_mgc_calloc(), mem_mgc_head(), mem_mgc_add_block(), 
 *      mem_mgc_create_block()
 */
void mem_mgc_free(void);

/**
 * @brief Returns the address of the pointer to the head of the internal list of 
 *        managed blocks.
 *
 * The `mem_mgc_head()` function returns a double pointer to the head of the 
 * internal linked list used by the memory manager. Each allocation or manual 
 * block addition modifies this list.
 *
 * @return t_mem_mgc_block** A double pointer to the first element of the 
 *         managed blocks list.
 *
 * @note This function is primarily for internal use by the memory manager.
 *       Using it directly requires a good understanding of the internal 
 *       workings.
 *
 * @warning Manipulating the list outside of the provided functions may lead 
 *          to memory leaks or undefined behavior.
 *
 * @see mem_mgc_add_block(), mem_mgc_create_block(), mem_mgc_alloc(), 
 *      mem_mgc_calloc()
 */
t_mem_mgc_block **mem_mgc_head(void);

/**
 * @brief Adds an already allocated memory block to the memory manager.
 *
 * The `mem_mgc_add_block()` function takes a pointer to a memory block
 * that has already been allocated by other means (e.g., `malloc`) and adds it 
 * to the internal list of managed blocks. A custom free function can be 
 * specified; otherwise, `free` is used by default. This ensures that the block 
 * will be automatically freed when `mem_mgc_free()` is called.
 *
 * @param block The pointer to the already allocated memory block.
 * @param free_func A pointer to a custom memory free function.
 *                  If `NULL`, the standard `free` function will be used.
 *
 * @return void* The pointer to the added block, or `NULL` on failure.
 *
 * @warning
 * - Do not manually free this block by other means after adding it.
 *   The manager will handle it during `mem_mgc_free()`.
 * - This function is not thread-safe. In a multi-threaded environment,
 *   protect its call with a mutex or another synchronization mechanism.
 *
 * @see mem_mgc_create_block(), mem_mgc_free(), mem_mgc_alloc(), 
 *      mem_mgc_calloc().
 */
void *mem_mgc_add_block(void *block, void (*free_func)(void *));

/**
 * @brief Allocates a new memory block and registers it in the internal list of 
 *        managed blocks.
 *
 * The `mem_mgc_create_block()` function performs a new memory allocation of the
 * specified size and adds it to the memory manager, along with a free function 
 * (custom or default `free`).
 * The block will thus be automatically freed when `mem_mgc_free()` is called.
 *
 * @param size The size in bytes of the memory block to allocate.
 * @param free_func A pointer to a custom memory free function.
 *                  If `NULL`, the standard `free` function will be used.
 *
 * @return void* A pointer to the newly allocated memory block.
 *
 * @exception On allocation failure (either the block or the internal structure),
 *            the function calls `exit(EXIT_FAILURE)` and terminates the program.
 *
 * @warning
 * - This function is not thread-safe.
 * - On allocation failure, the program will terminate.
 *
 * @see mem_mgc_add_block(), mem_mgc_free(), mem_mgc_alloc(), mem_mgc_calloc()
 */
void *mem_mgc_create_block(size_t size, void (*free_func)(void *));

/**
 * @brief Allocates memory with automatic management (memory manager).
 *
 * The `mem_mgc_alloc` function allocates a memory block of the specified size 
 * and registers it with the memory manager. The allocated memory will be 
 * automatically freed when the memory manager is cleared, helping to prevent 
 * memory leaks.
 *
 * @param size The size in bytes of the memory block to allocate.
 * @param free_func A pointer to a custom memory free function.
 *                  If `NULL`, the standard `free` function will be used by 
 *                  default.
 *
 * @return void* A pointer to the allocated memory block, or `NULL` if:
 *               - The requested size is zero.
 *               - Memory allocation fails.
 *               - Allocation of a new management block fails.
 *
 * @details
 * This function facilitates memory management by registering each allocated 
 * block in an internal list. Each block is associated with a free function that
 * will be called when the entire managed memory is freed. This centralizes 
 * memory release management and reduces the risk of memory leaks.
 *
 * **Usage:**
 * ```c
 * #include "mem_mgc.h"
 *
 * void custom_free(void *ptr)
 * {
 *     // Custom memory release implementation
 *     free(ptr);
 * }
 *
 * int main(void)
 * {
 *     // Allocation with the default free function (`free`)
 *     int *numbers = mem_mgc_alloc(10 * sizeof(int), NULL);
 *
 *     // Allocation with a custom free function
 *     char *buffer = mem_mgc_alloc(256, custom_free);
 *
 *     // Use the allocated blocks...
 *
 *     // Free all memory blocks managed by the memory manager
 *     mem_mgc_free();
 *
 *     return 0;
 * }
 * ```
 *
 * @warning
 * - Ensure you call `mem_mgc_free()` before the end of your program to free
 *   all allocated memory blocks and avoid leaks.
 * - This function is not thread-safe. If your application is multi-threaded, 
 *   you must protect calls to `mem_mgc_alloc` with appropriate synchronization 
 *   mechanisms.
 *
 * @see mem_mgc_free()
 */
void	*mem_mgc_alloc(size_t size, void (*free_func)(void *));

/**
 * @brief Allocates memory and initializes it to zero with automatic management.
 *
 * The `mem_mgc_calloc` function allocates memory for an array of `nmemb` 
 * elements of `size` bytes each and initializes all bytes to zero. 
 * The allocated memory is registered with the memory manager and will be 
 * automatically freed when the manager is cleared.
 *
 * @param nmemb Number of elements to allocate.
 * @param size Size of each element in bytes.
 * @param free_func A pointer to a custom memory free function.
 *                  If `NULL`, the standard `free` function will be used by 
 *                  default.
 *
 * @return void* A pointer to the allocated and zero-initialized memory, 
 *               or `NULL` if:
 *               - The product `nmemb * size` is zero.
 *               - Memory allocation fails.
 *               - Allocation of a new management block fails.
 *
 * @details
 * This function behaves similarly to `mem_mgc_alloc` but additionally 
 * initializes the allocated memory to zero. It is useful for allocating arrays
 * or structures where initialization is required.
 *
 * **Usage:**
 * ```c
 * #include "mem_mgc.h"
 *
 * int main(void)
 * {
 *     // Allocate and zero-initialize an array of 50 integers
 *     int *array = mem_mgc_calloc(50, sizeof(int), NULL);
 *
 *     // Use the allocated array...
 *
 *     // Free all memory blocks managed by the memory manager
 *     mem_mgc_free();
 *
 *     return 0;
 * }
 * ```
 *
 * @warning
 * - Ensure you call `mem_mgc_free()` before the end of your program to free
 *   all allocated memory blocks and avoid leaks.
 * - This function is not thread-safe. If your application is multi-threaded, 
 *   you must protect calls to `mem_mgc_calloc` with appropriate synchronization
 *   mechanisms.
 *
 * @see mem_mgc_alloc(), mem_mgc_free()
 */
void	*mem_mgc_calloc(size_t nmemb, size_t size, void (*free_func)(void *));

#endif
