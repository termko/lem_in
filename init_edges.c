/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_edges.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 07:44:01 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/26 17:49:05 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_edges(t_lemin *lemin)
{
	int	i;
	int	j;
	int	**arr;

	check_malloc(arr = (int**)malloc(sizeof(int*) * lemin->node_count));
	i = 0;
	while (i < lemin->node_count)
	{
		check_malloc(arr[i] = (int*)malloc(sizeof(int) * lemin->node_count));
		j = 0;
		while (j < lemin->node_count)
		{
			arr[i][j] = 0;
			j++;
		}
		i++;
	}
	lemin->edges = arr;
}

int		node_index(t_lemin *lemin, char *name)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = lemin->nodes;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			return (i);
		i++;
		tmp = tmp->next;
	}
	error_msg("ERROR\n");
	return (-1);
}

void	update_edges(t_lemin *lemin, char *start, char *end)
{
	int		i;
	int		j;

	if (!lemin->edges)
		init_edges(lemin);
	if (!ft_strcmp(start, end))
		error_msg("ERROR\n");
	i = node_index(lemin, start);
	j = node_index(lemin, end);
	if (lemin->edges[i][j] || lemin->edges[j][i])
		error_msg("ERROR\n");
	lemin->edges[i][j] = 1;
	lemin->edges[j][i] = 1;
}
