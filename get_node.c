/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 07:15:49 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/15 07:18:12 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_node	*get_node(t_lemin *lemin, char **split)
{
	t_node *node;

	if (!lemin->nodes)
	{
		check_malloc(lemin->nodes = (t_node*)malloc(sizeof(t_node)));
		node = lemin->nodes;
	}
	else
	{
		node = lemin->nodes;
		while (node->next)
		{
			if (!ft_strcmp(node->name, split[0]) ||
					coord_check(node->loc, split))
				error_msg("ERROR\n");
			node = node->next;
		}
		if (!ft_strcmp(node->name, split[0]) ||
				coord_check(node->loc, split))
			error_msg("ERROR\n");
		check_malloc(node->next = (t_node*)malloc(sizeof(t_node)));
		node = node->next;
	}
	return (node);
}
