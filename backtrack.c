/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtrack.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 09:09:47 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/22 19:24:49 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		count_backtrack(t_lemin *lemin, int i)
{
	int		count;

	count = 1;
	while (i != lemin->start_index)
	{
		count++;
		i = lemin->edges[i][i] - 1;
		if (i < 0)
			return (-1);
	}
	return (count);
}

int		fill_path(t_lemin *lemin, int j, int prev)
{
	lemin->edges[prev][j] = 0;
	if (lemin->edges[j][prev] == -1)
		lemin->edges[j][prev] = 0;
	else if (lemin->edges[j][prev])
		lemin->edges[j][prev] = -1;
	return (prev);
}

t_path	*backtrack(t_lemin *lemin)
{
	t_path	*path;
	int		count;
	int		i;
	int		j;
	int		prev;

	count = count_backtrack(lemin, lemin->end_index);
	if (count < 0)
		return (NULL);
	path = new_path(lemin, count);
	path->path[count - 1] = lemin->end_node;
	i = count - 2;
	j = lemin->end_index;
	while (i >= 0)
	{
		prev = lemin->edges[j][j] - 1;
		j = fill_path(lemin, j, prev);
		path->path[i] = find_node(lemin, lemin->names[prev]);
		if (path->path[i] == lemin->start_node)
			return (path);
		i--;
	}
	return (path);
}
