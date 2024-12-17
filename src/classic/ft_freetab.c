/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freetab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 13:02:37 by antoinemura       #+#    #+#             */
/*   Updated: 2024/12/17 02:44:41 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	ft_freetab(void **tab)
{
	int	i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_free(tab + i);
		i++;
	}
	ft_free((void **) &tab);
}
