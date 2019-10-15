/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 18:11:38 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/15 08:16:54 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include <stdio.h> // DELETE ME

typedef struct	s_v2
{
	int		x;
	int		y;
}				t_v2;

typedef struct	s_node
{
	t_v2				loc;
	char				*name;
	int					start;
	int					end;
	uintmax_t			ants;
	int					link_count;
	struct s_node		*next;
}				t_node;

typedef struct	s_path
{
	t_node				**path;
	int					*stepped;
	uintmax_t			ants;
	uintmax_t			ant_max;
	struct s_path		*next;
}				t_path;

typedef struct	s_ant
{
	t_path		*path;
	int			curr_node;
	int			at_end;
}				t_ant;

typedef struct	s_out
{
	char			*str;
	struct s_out	*next;
}				t_out;

typedef struct	s_lemin
{
	t_node			*nodes;
	t_node			*start_node;
	t_node			*end_node;
	t_path			*paths;
	t_ant			**ants;
	t_out			*out;
	char			**names;
	int				**edges;
	int				*fastest;
	int				*visited;
	int				node_count;
	int				link_count;
	uintmax_t		ant_count;
	int				start_index;
	int				end_index;
	int				comment;
	int				start;
	int				end;
	int				part;
}				t_lemin;

t_lemin			*init_lemin(void);
void			init_ants(t_lemin *lemin);
void			init_node(t_lemin *lemin, char **split);
t_node			*get_node(t_lemin *lemin, char **split);
int				check_first(t_lemin *lemin, char *buff);
int				check_second(t_lemin *lemin, char *buff);
int				check_third(t_lemin *lemin, char *buff);
void			check_malloc(void *addr);
void			error_msg(char *msg);
int				split_check(char **split, int count);
void			split_free(char ***split);
int				coord_check(t_v2 loc, char **split);
void			update_edges(t_lemin *lemin, char **split);
void			fill_names(t_lemin *lemin);
void			read_map(t_lemin *lemin);
#endif
