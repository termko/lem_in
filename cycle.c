/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 09:50:49 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/17 11:08:56 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		set_ants(t_lemin *lemin, t_path *path, uintmax_t i)
{
	path->ants = lemin->ant_count - i;
	while (i < lemin->ant_count)
	{
		lemin->ants[i]->path = path;
		i++;
	}
	return (i);
}

int		spread_ants(t_lemin *lemin, t_path *path, uintmax_t i)
{
	uintmax_t	j;

	j = 0;
	path->ants = path->ant_max;
	while (j < path->ant_max)
	{
		lemin->ants[i + j]->path = path;
		j++;
	}
	return (i + j);
}

int		ant_step(t_lemin *lemin, uintmax_t ind, int flag)
{
	t_path	*path;
	t_ant	*ant;
	int		node;

	ant = lemin->ants[ind];
	path = ant->path;
	node = ant->curr_node;
	if (path->stepped[node + 1] || (path->path[node + 1]->ants &&
				!path->path[node + 1]->end))
		return (0);
	path->path[node + 1]->ants++;
	path->stepped[node + 1] = 1;
	path->path[node]->ants--;
	ant->curr_node++;
	if (path->path[ant->curr_node]->end)
	{
		path->ants--;
		ant->at_end = 1;
	}
	if (flag)
		write(1, " ", 1);
	print_ant_path(ind + 1, path->path[ant->curr_node]->name);
	return (1);
}

void	step(t_lemin *lemin)
{
	uintmax_t	i;
	int			end;
	int			flag;

	end = 0;
	while (!end)
	{
		end = 1;
		flag = 0;
		i = -1;
		clear_stepped(lemin);
		while (++i < lemin->ant_count)
			if (!lemin->ants[i]->at_end)
			{
				if (ant_step(lemin, i, flag))
				{
					flag = 1;
					end = 0;
				}
			}
		if (!end)
			ft_putchar('\n');
	}
}

void	cycle(t_lemin *lemin)
{
	uintmax_t	i;
	t_path		*path;

	i = 0;
	path = lemin->paths;
	while (i < lemin->ant_count)
	{
		if (lemin->ant_count - i < path->ant_max)
			i = set_ants(lemin, path, i);
		else
			i = spread_ants(lemin, path, i);
		if (!path->next)
			path = lemin->paths;
		else
			path = path->next;
	}
	step(lemin);
}
