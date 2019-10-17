/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:01:45 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/17 11:07:38 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	print_ant_path(uintmax_t index, char *path)
{
	char *str_ind;

	check_malloc(str_ind = ft_uintmaxtoa(index, 10));
	ft_putchar('L');
	ft_putstr(str_ind);
	ft_putchar('-');
	ft_putstr(path);
	ft_strdel(&str_ind);
}

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
		write(1, out->str, ft_strlen(out->str));
		ft_putchar('\n');
		out = out->next;
	}
	ft_putchar('\n');
}
