/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 08:14:10 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/15 08:16:20 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_ants(t_lemin *lemin)
{
	t_ant			**ants;
	uintmax_t		i;

	if (lemin->ant_count + 1 < lemin->ant_count)
		error_msg("ERROR\n");
	check_malloc(ants = (t_ant**)malloc(sizeof(t_ant*) *
				(lemin->ant_count + 1)));
	i = 0;
	while (i < lemin->ant_count)
	{
		check_malloc(ants[i] = (t_ant*)malloc(sizeof(t_ant)));
		ants[i]->path = NULL;
		ants[i]->curr_node = 0;
		ants[i]->at_end = 0;
		i++;
	}
	ants[i] = NULL;
	lemin->ants = ants;
}
