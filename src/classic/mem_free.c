/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:12:51 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/17 18:12:51 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	mem_free(void **addr)
{
	free(*addr);
	*addr = NULL;
}

void	mem_vfree(int count, ...)
{
	int		i;
	va_list	lst;
	void	**tofree;

	i = 0;
	va_start(lst, count);
	while (i < count)
	{
		tofree = va_arg(lst, void *);
		free(*tofree);
		*tofree = NULL;
		i++;
	}
}
