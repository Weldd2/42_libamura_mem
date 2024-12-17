/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 20:15:45 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/17 02:53:29 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# define ARENA_BLOC_SIZE 65536
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_arena_mem_block_list
{
	struct s_arena_mem_block_list	*next;
	void			*block;
}	t_arena_mem_block_list;

void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	ft_bzero(void *s, size_t n);
void	*ft_memmove(void *dest, void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_freetab(void **tab);
void	ft_free(void **addr);
void	ft_vfree(int count, ...);

/**
 * @brief Libère toute la mémoire allouée par l'arène.
 *
 * Cette fonction parcourt tous les blocs de l'arène et les libère,
 * puis réinitialise la tête de l'arène à NULL.
 */
void	ft_free_arena(void);

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
void	*ft_arena_alloc(size_t size);


#endif