/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_classic.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:51:51 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/18 20:53:50 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_CLASSIC_H
# define MEM_CLASSIC_H
# include <stdio.h>
# include <stdarg.h>

void	*mem_memset(void *s, int c, size_t n);
void	*mem_memcpy(void *dest, const void *src, size_t n);
void	mem_bzero(void *s, size_t n);
void	*mem_memmove(void *dest, void *src, size_t n);
void	*mem_memchr(const void *s, int c, size_t n);
int		mem_memcmp(const void *s1, const void *s2, size_t n);
void	*mem_realloc(void *ptr, size_t old_size, size_t new_size);
void	*mem_calloc(size_t nmemb, size_t size);
void	mem_freetab(void **tab);
void	mem_free(void **addr);
void	mem_vfree(int count, ...);

#endif