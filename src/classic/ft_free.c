/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:05:52 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/17 02:52:54 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	ft_free(void **addr)
{
	free(*addr);
	*addr = NULL;
}

void	ft_vfree(int count, ...)
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
