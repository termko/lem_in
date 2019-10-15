/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 07:50:12 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/15 07:58:23 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		check_numerical(char *buff)
{
	int		i;

	i = 0;
	while (buff[i])
	{
		if (!ft_isdigit(buff[i]))
			return (1);
		i++;
	}
	return (0);
}

int		check_comment(t_lemin *lemin, char *buff)
{
	if (buff[0] == '#')
	{
		if (buff[1] != '#')
			lemin->comment = 1;
		else if (!ft_strcmp((buff + 2), "start"))
			lemin->start = 1;
		else if (!ft_strcmp((buff + 2), "end"))
			lemin->end = 1;
		return (1);
	}
	lemin->comment = 0;
	return (0);
}

int		check_first(t_lemin *lemin, char *buff)
{
	if (check_comment(lemin, buff))
		return (0);
	if (check_numerical(buff))
		error_msg("ERROR\n");
	lemin->ant_count = ft_atoi(buff);
	if (!lemin->ant_count)
		error_msg("ERROR\n");
	lemin->part++;
	return (0);
}

int		check_second(t_lemin *lemin, char *buff)
{
	char **split;

	if (check_comment(lemin, buff))
		return (0);
	check_malloc(split = ft_strsplit(buff, ' '));
	if (split_check(split, 3))
	{
		split_free(&split);
		lemin->part++;
		return (check_third(lemin, buff));
	}
	if (split[0][0] == 'L' || check_numerical(split[1]) ||
			check_numerical(split[2]))
		error_msg("ERROR\n");
	lemin->node_count++;
	init_node(lemin, split);
	split_free(&split);
	return (0);
}

int		check_third(t_lemin *lemin, char *buff)
{
	char **split;

	if (check_comment(lemin, buff))
		return (0);
	check_malloc(split = ft_strsplit(buff, '-'));
	if (split_check(split, 2))
	{
		split_free(&split);
		return (1);
	}
	if (!ft_strcmp(split[0], split[1]))
		error_msg("ERROR\n");
	lemin->link_count++;
	update_edges(lemin, split);
	split_free(&split);
	return (0);
}
