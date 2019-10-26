/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 07:50:12 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/26 17:57:29 by ydavis           ###   ########.fr       */
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

char	*find_str(t_lemin *lemin, char *str)
{
	t_node	*node;
	char	*ret;

	node = lemin->nodes;
	ret = NULL;
	while (node)
	{
		if ((ret = ft_strstr(str, node->name)) == str)
		{
			ret = node->name;
			break ;
		}
		node = node->next;
	}
	if (!node)
		error_msg("ERROR\n");
	return (ret);
}


int		check_third(t_lemin *lemin, char *str)
{
	char	*start;
	char	*end;

	if (check_comment(lemin, str))
		return (0);
	start = find_str(lemin, str);
	str += ft_strlen(start);
	if (*str != '-')
		error_msg("ERROR\n");
	str++;
	end = find_str(lemin, str);
	lemin->link_count++;
	update_edges(lemin, start, end);
	return (0);
}
