/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lemin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 09:48:15 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/15 09:49:48 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_edges(t_lemin *lemin)
{
	int		i;

	i = 0;
	while (i < lemin->node_count)
	{
		free(lemin->edges[i]);
		i++;
	}
	free(lemin->edges);
}

void	free_lemin(t_lemin **lemin)
{
	free_nodes(*lemin);
	free_out(*lemin);
	free_paths(*lemin);
	free_ants(*lemin);
	free_names(*lemin);
	free_edges(*lemin);
	free((*lemin)->visited);
	free((*lemin)->fastest);
	free(*lemin);
}
