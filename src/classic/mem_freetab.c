/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_freetab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:12:44 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/17 18:12:44 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	mem_freetab(void **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		mem_free(tab + i);
		i++;
	}
	mem_free((void **) &tab);
}
