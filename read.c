/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 07:59:42 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/15 08:19:14 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		check_str(t_lemin *lemin, char *buff)
{
	if (!*buff)
		return (1);
	if (lemin->part == 0)
		return (check_first(lemin, buff));
	if (lemin->part == 1)
		return (check_second(lemin, buff));
	if (lemin->part == 2)
		return (check_third(lemin, buff));
	return (1);
}

void	append_str(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	str[i] = c;
}

char	*read_line(void)
{
	char	*buff;
	char	c;

	check_malloc(buff = ft_strnew(1024));
	while (1)
	{
		if (read(STDIN_FILENO, &c, 1) <= 0)
		{
			free(buff);
			return (NULL);
		}
		if (c == '\0')
		{
			free(buff);
			return (NULL);
		}
		if (c == '\n')
		{
			if (buff[0])
				return (buff);
			free(buff);
			return (NULL);
		}
		append_str(buff, c);
	}
}

void	append_out(t_lemin *lemin, char *str)
{
	t_out	*out;

	if (!lemin->out)
	{
		check_malloc(lemin->out = (t_out*)malloc(sizeof(t_out)));
		out = lemin->out;
	}
	else
	{
		out = lemin->out;
		while (out->next)
			out = out->next;
		check_malloc(out->next = (t_out*)malloc(sizeof(t_out)));
		out = out->next;
	}
	check_malloc(out->str = ft_strdup(str));
	out->next = NULL;
}

void	read_map(t_lemin *lemin)
{
	char	*buff;

	while (1)
	{
		if (!(buff = read_line()))
			break ;
		if (check_str(lemin, buff))
			break ;
		append_out(lemin, buff);
		free(buff);
	}
	if (lemin->node_count < 2 || lemin->link_count < 1 || (buff = read_line()))
		error_msg("ERROR\n");
	fill_names(lemin);
}
