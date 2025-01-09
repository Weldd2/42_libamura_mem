/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoinemura <antoinemura@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 18:12:51 by antoinemura       #+#    #+#             */
/*   Updated: 2025/01/09 23:32:02 by antoinemura      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"

void	mem_free(void *ptr)
{
	t_mem_header *header;

	if (!ptr)
		return ;
	header = (t_mem_header *)ptr - 1;
	free(header);
}
