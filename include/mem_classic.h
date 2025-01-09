/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_classic.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:51:51 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/09 23:23:50 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_CLASSIC_H
# define MEM_CLASSIC_H
# include <stdio.h>
# include <stdarg.h>

# define ALIGNMENT 8

void	*mem_memset(void *s, int c, size_t n);
void	*mem_memcpy(void *dest, const void *src, size_t n);
void	mem_bzero(void *s, size_t n);
void	*mem_memmove(void *dest, void *src, size_t n);
void	*mem_memchr(const void *s, int c, size_t n);
int		mem_memcmp(const void *s1, const void *s2, size_t n);
void	*mem_calloc(size_t nmemb, size_t size);
void	mem_freetab(void **tab);

typedef struct s_mem_header
{
	size_t	size;
}	t_mem_header;

void	*mem_realloc(void *ptr, size_t size);

void	*mem_malloc(size_t size);

void	mem_free(void *ptr);

#endif