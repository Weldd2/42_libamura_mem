/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_memmove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:13:15 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/17 18:13:16 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	*mem_memmove(void *dest, void *src, size_t n)
{
	char	*d;
	char	*s;

	d = dest;
	s = src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (d < s)
	{
		while (n--)
			*(unsigned char *)d++ = *(unsigned char *)s++;
	}
	else
	{
		while (n--)
			*((unsigned char *)(d + n)) = *((unsigned char *)(s + n));
	}
	return (dest);
}
