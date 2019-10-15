/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:01:45 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/15 10:18:25 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	clear_stepped(t_lemin *lemin)
{
	int		i;
	t_path	*path;

	path = lemin->paths;
	while (path)
	{
		i = 0;
		while (path->path[i])
		{
			path->stepped[i] = 0;
			i++;
		}
		path = path->next;
	}
}

void	check_read(t_lemin *lemin)
{
	if (!lemin->start_node || !lemin->end_node)
		error_msg("ERROR\n");
}

void	print_map(t_lemin *lemin)
{
	t_out	*out;

	out = lemin->out;
	while (out)
	{
		printf("%s\n", out->str); // DELETE ME
		out = out->next;
	}
	printf("\n"); // DELETE ME
}
