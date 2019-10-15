/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 18:11:05 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/15 08:46:17 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	fill_names(t_lemin *lemin)
{
	t_node	*tmp;
	int		i;

	tmp = lemin->nodes;
	check_malloc(lemin->names = (char**)malloc(sizeof(char*) *
				(lemin->node_count + 1)));
	i = 0;
	while (tmp)
	{
		check_malloc(lemin->names[i] = ft_strdup(tmp->name));
		if (tmp->start)
			lemin->start_index = i;
		else if (tmp->end)
			lemin->end_index = i;
		i++;
		tmp = tmp->next;
	}
	lemin->names[i] = NULL;
}

/*
void	init_ants(t_lemin *lemin)
{
	t_ant			**ants;
	uintmax_t		i;

	if (lemin->ant_count + 1 < lemin->ant_count)
		error_msg("ERROR\n");
	check_malloc(ants = (t_ant**)malloc(sizeof(t_ant*) *
				(lemin->ant_count + 1)));
	i = 0;
	while (i < lemin->ant_count)
	{
		check_malloc(ants[i] = (t_ant*)malloc(sizeof(t_ant*)));
		ants[i]->path = NULL;
		ants[i]->curr_node = 0;
		ants[i]->at_end = 0;
		i++;
	}
	ants[i] = NULL;
	lemin->ants = ants;
}
*/

int		count_backtrack(t_lemin *lemin, int i)
{
	int	count;

	count = 1;
	while (i != lemin->start_index)
	{
		count++;
		i = lemin->edges[i][i] - 1;
		if (i < 0)
			return (-1);
	}
	return (count);
}

void	clear_prev(t_lemin *lemin, int prev, int i)
{
	int j;

	j = 0;
	while (j < lemin->node_count)
	{
		if (j != i && lemin->edges[j][j] == prev + 1)
			lemin->edges[j][j] = 0;
		j++;
	}
}

t_node	*find_node(t_lemin *lemin, char *name)
{
	t_node	*ret;

	ret = lemin->nodes;
	while (ret)
	{
		if (!ft_strcmp(ret->name, name))
			return (ret);
		ret = ret->next;
	}
	return (ret);
}

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

void	clear_visited(t_lemin *lemin)
{
	int	i;

	i = 0;
	while (i < lemin->node_count)
	{
		lemin->visited[i] = 0;
		i++;
	}
}

t_path	*backtrack(t_lemin *lemin)
{
	t_path	*path;
	int		count;
	int		i;
	int		j;
	int		prev;

	clear_visited(lemin);
	count = count_backtrack(lemin, lemin->end_index);
	if (count < 0)
		return (NULL);
	path = new_path(lemin, count);
	path->path[count - 1] = lemin->end_node;
	i = count - 2;
	j = lemin->end_index;
	while (i >= 0)
	{
		prev = lemin->edges[j][j] - 1;
		lemin->edges[prev][j] = 0;
		if (lemin->edges[j][prev] == -1)
			lemin->edges[j][prev] = 0;
		else if (lemin->edges[j][prev])
			lemin->edges[j][prev] = -1;
		path->path[i] = find_node(lemin, lemin->names[prev]);
		if (path->path[i] == lemin->start_node)
			return (path);
		clear_prev(lemin, prev, j);
		j = prev;
		i--;
	}
	return (path);
}

void	init_fastest(t_lemin *lemin)
{
	int		i;

	if (!lemin->fastest)
		check_malloc(lemin->fastest = (int*)malloc(sizeof(int) *
					lemin->node_count));
	i = 0;
	while (i < lemin->node_count)
	{
		lemin->fastest[i] = lemin->node_count + 1;
		i++;
	}
	lemin->fastest[lemin->start_index] = 0;
}

int		least_dist(t_lemin *lemin)
{
	int		i;
	int		least;
	int		min;

	i = 0;
	min = lemin->node_count + 1;
	least = -1;
	while (i < lemin->node_count)
	{
		if (lemin->fastest[i] < min && !lemin->visited[i])
		{
			min = lemin->fastest[i];
			least = i;
		}
		i++;
	}
	return (least);
}

t_path	*dijkstra(t_lemin *lemin)
{
	int		i;
	int		j;
	int		dist;

	init_fastest(lemin);
	while (1)
	{
		if ((i = least_dist(lemin)) < 0)
			break ;
		lemin->visited[i] = 1;
		j = 0;
		while (j < lemin->node_count)
		{
			if (i != j && lemin->edges[i][j] && !lemin->visited[j])
			{
				dist = lemin->edges[i][j] + lemin->fastest[i];
				if (lemin->fastest[j] > dist)
				{
					lemin->edges[j][j] = i + 1;
					lemin->fastest[j] = dist;
				}
			}
			j++;
		}
	}
	return (backtrack(lemin));
}

void	init_visited(t_lemin *lemin)
{
	int	i;

	if (!lemin->visited)
		check_malloc(lemin->visited = (int*)malloc(sizeof(int) * lemin->node_count));
	i = 0;
	while (i < lemin->node_count)
	{
		lemin->visited[i] = 0;
		i++;
	}
}

void	clear_edges(t_lemin *lemin)
{
	int i;

	i = 0;
	while (i < lemin->node_count)
	{
		lemin->edges[i][i] = 0;
		i++;
	}
}

void	check_bottlenecks(t_lemin *lemin)
{
	int		i;
	int		j;

	i = 0;
	while (i < lemin->node_count)
	{
		j = 0;
		while (j < lemin->node_count)
		{
			if (lemin->edges[i][j])
			{
				lemin->edges[i][j] = 1;
				lemin->edges[j][i] = 1;
			}
			j++;
		}
		i++;
	}
}

void	free_paths(t_lemin *lemin)
{
	t_path	*path;

	while (lemin->paths)
	{
		path = lemin->paths->next;
		free(lemin->paths->stepped);
		free(lemin->paths->path);
		free(lemin->paths);
		lemin->paths = path;
	}
	lemin->paths = NULL;
}

int		check_flow(t_lemin *lemin)
{
	t_path			*path;
	uintmax_t	flow;

	flow = 0;
	path = lemin->paths;
	while (path)
	{
		flow += path->ant_max;
		if (flow >= lemin->ant_count)
			return (1);
		path = path->next;
	}
	return (0);
}

void	max_flow(t_lemin *lemin, int flag)
{
	int		ind;

	ind = lemin->start_index;
	init_visited(lemin);
	while (dijkstra(lemin))
	{
		init_visited(lemin);
		clear_edges(lemin);
		if (flag && check_flow(lemin))
			return ;
	}
	if (!lemin->paths)
		error_msg("ERROR\n");
	if (!flag)
	{
		free_paths(lemin);
		check_bottlenecks(lemin);
		max_flow(lemin, 1);
	}
}

int		ant_step(t_lemin *lemin, int ind, int flag)
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
		printf(" ");
	printf("L%d-%s", ind + 1, path->path[ant->curr_node]->name);
	return (1);
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

void	step(t_lemin *lemin)
{
	uintmax_t	i;
	int			end;
	int			flag;

	end = 0;
	while (!end)
	{
		flag = 0;
		end = 1;
		i = 0;
		clear_stepped(lemin);
		while (i < lemin->ant_count)
		{
			if (!lemin->ants[i]->at_end)
			{
				if (ant_step(lemin, i, flag))
				{
					end = 0;
					flag = 1;
				}
			}
			i++;
		}
		if (!end)
			printf("\n");
	}
}

void	cycle(t_lemin *lemin)
{
	uintmax_t	i;
	uintmax_t	j;
	t_path		*path;

	i = 0;
	path = lemin->paths;
	while (i < lemin->ant_count)
	{
		if (lemin->ant_count - i < path->ant_max)
		{
			path->ants = lemin->ant_count - i;
			while (i < lemin->ant_count)
			{
				lemin->ants[i]->path = path;
				i++;
			}
		}
		else
		{
			j = 0;
			path->ants = path->ant_max;
			while (j < path->ant_max)
			{
				lemin->ants[i + j]->path = path;
				j++;
			}
			i += j;
		}
		if (!path->next)
			path = lemin->paths;
		else
			path = path->next;
	}
	step(lemin);
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
		printf("%s\n", out->str);
		out = out->next;
	}
	printf("\n");
}

void	free_nodes(t_lemin *lemin)
{
	t_node	*node;

	while (lemin->nodes)
	{
		node = lemin->nodes->next;
		free(lemin->nodes->name);
		free(lemin->nodes);
		lemin->nodes = node;
	}
}

void	free_out(t_lemin *lemin)
{
	t_out	*tmp;

	while (lemin->out)
	{
		tmp = lemin->out->next;
		free(lemin->out->str);
		free(lemin->out);
		lemin->out = tmp;
	}
}

void	free_ants(t_lemin *lemin)
{
	uintmax_t	i;

	i = 0;
	while (i < lemin->ant_count)
	{
		free(lemin->ants[i]);
		i++;
	}
	free(lemin->ants);
}

void	free_names(t_lemin *lemin)
{
	int		i;

	i = 0;
	while (lemin->names[i])
	{
		free(lemin->names[i]);
		i++;
	}
	free(lemin->names);
}

void	free_edges(t_lemin *lemin)
{
	int		i;

	i = 0;
	while (i < lemin->node_count)
	{
		free(lemin->edges[i]);
		i++;
	}
	free(lemin->edges);
}

void	free_lemin(t_lemin **lemin)
{
	free_nodes(*lemin);
	free_out(*lemin);
	free_paths(*lemin);
	free_ants(*lemin);
	free_names(*lemin);
	free_edges(*lemin);
	free((*lemin)->visited);
	free((*lemin)->fastest);
	free(*lemin);
}

int		main(void)
{
	t_lemin	*lemin;

	lemin = init_lemin();
	read_map(lemin);
	check_read(lemin);
	init_ants(lemin);
	max_flow(lemin, 0);
	print_map(lemin);
	cycle(lemin);
	free_lemin(&lemin);
//	sleep(5);
	return (0);
}
