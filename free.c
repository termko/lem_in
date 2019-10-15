/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 09:39:17 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/15 09:45:11 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	free_paths(t_lemin *lemin)
{
	t_path	*path;

	while (lemin->paths)
	{
		path = lemin->paths->next;
		free(lemin->paths->stepped);
		free(lemin->paths->path);
		free(lemin->paths);
		lemin->paths = path;
	}
}

void	free_nodes(t_lemin *lemin)
{
	t_node *node;

	while (lemin->nodes)
	{
		node = lemin->nodes->next;
		free(lemin->nodes->name);
		free(lemin->nodes);
		lemin->nodes = node;
	}
}

void	free_out(t_lemin *lemin)
{
	t_out	*tmp;

	while (lemin->out)
	{
		tmp = lemin->out->next;
		free(lemin->out->str);
		free(lemin->out);
		lemin->out = tmp;
	}
}

void	free_ants(t_lemin *lemin)
{
	uintmax_t	i;

	i = 0;
	while (i < lemin->ant_count)
	{
		free(lemin->ants[i]);
		i++;
	}
	free(lemin->ants);
}

void	free_names(t_lemin *lemin)
{
	int		i;

	i = 0;
	while (lemin->names[i])
	{
		free(lemin->names[i]);
		i++;
	}
	free(lemin->names);
}
