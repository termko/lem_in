/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 07:28:38 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/15 08:20:12 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	init_endnode(t_lemin *lemin, t_node *node)
{
	if (lemin->end_node)
		error_msg("ERROR\n");
	lemin->end_node = node;
	lemin->end = 0;
	node->end = 1;
}

void	init_startnode(t_lemin *lemin, t_node *node)
{
	if (lemin->start_node)
		error_msg("ERROR\n");
	node->ants = lemin->ant_count;
	node->start = 1;
	lemin->start = 0;
	lemin->start_node = node;
}

void	init_node(t_lemin *lemin, char **split)
{
	t_node *node;

	node = get_node(lemin, split);
	check_malloc(node->name = ft_strdup(split[0]));
	node->loc.x = ft_atoi(split[1]);
	node->loc.y = ft_atoi(split[2]);
	node->ants = 0;
	node->link_count = 0;
	node->start = 0;
	node->end = 0;
	if (lemin->end)
		init_endnode(lemin, node);
	else if (lemin->start)
		init_startnode(lemin, node);
	else if (lemin->start && lemin->end)
		error_msg("ERROR\n");
	node->next = NULL;
}
