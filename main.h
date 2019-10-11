/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 18:11:38 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/11 07:30:39 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct	s_v2
{
	int		x;
	int		y;
}				t_v2;
typedef struct	s_node
{
	t_v2			loc;
	char			*name;
	int				start;
	int				end;
	int				ants;
	int				link_count;
	struct s_node	*next;
}				t_node;
typedef struct	s_ant
{
	t_node		*curr_node;
	t_node		*next_node;
	int			at_end;
}				t_ant;
typedef struct	s_stack
{
	int			cap;
	int			start;
	int			size;
	int			store[0];
}				t_stack;
typedef struct	s_lemin
{
	t_node		*nodes;
	t_node		*start_node;
	t_node		*end_node;
	t_ant		**ants;
	char		**names;
	int			**edges;
	int			*visited;
	int			node_count;
	int			link_count;
	int			ant_count;
	int			comment;
	int			start;
	int			end;
	int			part;
}				t_lemin;
int				check_third(t_lemin *lemin, char *buff);
#endif
