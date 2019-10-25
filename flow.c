/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 09:31:13 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/22 19:32:05 by ydavis           ###   ########.fr       */
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

int	best_flow(t_lemin *lemin)
{
	uintmax_t	count;
	t_path		*path;

	path = lemin->paths;
	count = 0;
	while (path)
	{
		count += path->ant_max;
		if (count > lemin->ant_count)
			return (1);
		path = path->next;
	}
	return (0);
}

void	max_flow(t_lemin *lemin, int flag)
{
	int	check;

	check = 0;
	init_visited(lemin);
	while (dijkstra(lemin))
	{
		clear_visited(lemin);
		clear_edges(lemin);
		if (!check && best_flow(lemin))
			return ;
		check = 1;
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
