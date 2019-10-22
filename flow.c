/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 09:31:13 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/18 17:58:43 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_visited(t_lemin *lemin)
{
	int		i;

	if (!lemin->visited)
		check_malloc(lemin->visited = (int*)malloc(sizeof(int) *
					lemin->node_count));
	i = 0;
	while (i < lemin->node_count)
	{
		lemin->visited[i] = 0;
		i++;
	}
}

void	clear_edges(t_lemin *lemin)
{
	int	i;

	i = 0;
	while (i < lemin->node_count)
	{
		lemin->edges[i][i] = 0;
		i++;
	}
}

void	check_bottlenecks(t_lemin *lemin)
{
	int		i;
	int		j;

	i = 0;
	while (i < lemin->node_count)
	{
		j = 0;
		while (j < lemin->node_count)
		{
			if (lemin->edges[i][j])
			{
				lemin->edges[i][j] = 1;
				lemin->edges[j][i] = 1;
			}
			j++;
		}
		i++;
	}
}

void	max_flow(t_lemin *lemin, int flag)
{
	int		ind;

	ind = lemin->start_index;
	init_visited(lemin);
	while (dijkstra(lemin))
	{
		init_visited(lemin);
		clear_edges(lemin);
	}
	if (!lemin->paths)
		error_msg("ERROR\n");
	if (!flag)
	{
		free_paths(lemin);
		check_bottlenecks(lemin);
		max_flow(lemin, 1);
	}
}
