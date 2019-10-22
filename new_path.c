/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 09:20:47 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/17 16:45:37 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

t_path	*new_path(t_lemin *lemin, int count)
{
	t_path	*new;

	if (!lemin->paths)
	{
		check_malloc(lemin->paths = (t_path*)malloc(sizeof(t_path)));
		new = lemin->paths;
	}
	else
	{
		new = lemin->paths;
		while (new->next)
			new = new->next;
		check_malloc(new->next = (t_path*)malloc(sizeof(t_path)));
		new = new->next;
	}
	check_malloc(new->path = (t_node**)malloc(sizeof(t_node*) * (count + 1)));
	new->path[count] = NULL;
	new->ants = 0;
	check_malloc(new->stepped = (int*)malloc(sizeof(int) * count));
	new->ant_max = count - 1;
	new->next = NULL;
	return (new);
}
