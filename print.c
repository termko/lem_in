/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 10:01:45 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/22 19:25:36 by ydavis           ###   ########.fr       */
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

int		check_out(t_out *out)
{
	if (out->str[0] == '#')
	{
		if (out->str[1] == '#')
		{
			if (out->str[2] == '#')
				return (1);
			if (!ft_strcmp("start", (out->str) + 2) ||
					!ft_strcmp("end", (out->str) + 2))
				return (1);
			return (0);
		}
	}
	return (1);
}

void	print_map(t_lemin *lemin)
{
	t_out	*out;

	out = lemin->out;
	while (out)
	{
		if (check_out(out))
		{
			write(1, out->str, ft_strlen(out->str));
			ft_putchar('\n');
		}
		out = out->next;
	}
	ft_putchar('\n');
}
