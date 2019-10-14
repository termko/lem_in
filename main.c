/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 18:11:05 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/15 02:33:43 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h> // DELETE THIS

void	check_malloc(void *addr)
{
	if (!addr)
	{
		ft_putstr_fd("Unexpected error with malloc! Exiting...\n",
				STDERR_FILENO);
		exit(1);
	}
}

void	error_msg(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(1);
}

int		split_check(char **split, int count)
{
	int i;

	i = 0;
	while (i < count)
	{
		if (!split[i])
			return (1);
		i++;
	}
	if (split[i])
		return (1);
	return (0);
}

void	split_free(char ***split)
{
	(void)split;
	/*
	char	*tmp;
	int		i;

	tmp = *split;
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
	*/
}

void	init_node(t_lemin *lemin, char **split)
{
	t_node	*node;
	if (!lemin->nodes)
	{
		check_malloc(lemin->nodes = (t_node*)malloc(sizeof(t_node)));
		node = lemin->nodes;
	}
	else
	{
		node = lemin->nodes;
		while (node->next)
		{
			if (!ft_strcmp(node->name, split[0]))
				error_msg("ERROR\n");
			node = node->next;
		}
		check_malloc(node->next = (t_node*)malloc(sizeof(t_node)));
		node = node->next;
	}
	check_malloc(node->name = ft_strdup(split[0]));
	node->loc.x = ft_atoi(split[1]);
	node->loc.y = ft_atoi(split[2]);
	node->ants = 0;
	node->link_count = 0;
	if (lemin->end)
	{
		lemin->end_node = node;
		lemin->end = 0;
		node->end = 1;
	}
	else if (lemin->start)
	{
		node->ants = lemin->ant_count;
		node->start = 1;
		lemin->start = 0;
		lemin->start_node = node;
	}
	node->next = NULL;
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

void	init_edges(t_lemin *lemin)
{
	int	i;
	int	j;
	int	**arr;

	check_malloc(arr = (int**)malloc(sizeof(int*) * lemin->node_count));
	i = 0;
	while (i < lemin->node_count)
	{
		check_malloc(arr[i] = (int*)malloc(sizeof(int) * lemin->node_count));
		j = 0;
		while (j < lemin->node_count)
		{
			arr[i][j] = 0;
			j++;
		}
		i++;
	}
	lemin->edges = arr;
}

int		index_of_node(t_lemin *lemin, char *name)
{
	t_node	*tmp;
	int		i;

	i = 0;
	tmp = lemin->nodes;
	while (tmp)
	{
		if (!ft_strcmp(name, tmp->name))
			return (i);
		i++;
		tmp = tmp->next;
	}
	error_msg("ERROR\n");
	return (-1);
}

void	update_edges(t_lemin *lemin, char **split)
{
	int		i;
	int		j;

	if (!lemin->edges)
		init_edges(lemin);
	if (!ft_strcmp(split[0], split[1]))
		return ;
	i = index_of_node(lemin, split[0]);
	j = index_of_node(lemin, split[1]);
	lemin->edges[i][j] = 1;
	lemin->edges[j][i] = 1;
}

int		check_first(t_lemin *lemin, char *buff)
{
	if (check_comment(lemin, buff))
		return (0);
	if ((lemin->ant_count = ft_atoi(buff)) < 0)
		error_msg("ERROR\n");
	lemin->part++;
	return (0);
}

int		check_second(t_lemin *lemin, char *buff)
{
	char	**split;

	if (check_comment(lemin, buff))
		return (0);
	check_malloc(split = ft_strsplit(buff, ' '));
	if (split_check(split, 3))
	{
		split_free(&split);
		if (lemin->node_count < 2)
			error_msg("ERROR\n");
		lemin->part++;
		return (check_third(lemin, buff));
	}
	if (split[0][0] == 'L')
		error_msg("ERROR\n");
	lemin->node_count++;
	init_node(lemin, split);
	split_free(&split);
	return (0);
}

int		check_third(t_lemin *lemin, char *buff)
{
	char	**split;

	if (check_comment(lemin, buff))
		return (0);
	check_malloc(split = ft_strsplit(buff, '-'));
	if (split_check(split, 2))
	{
		split_free(&split);
		if (lemin->link_count < 1)
			error_msg("ERROR\n");
		return (1);
	}
	lemin->link_count++;
	update_edges(lemin, split);
	split_free(&split);
	return (0);
}

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

void	read_map(t_lemin *lemin)
{
	char	*buff;

	while (1)
	{
		if (get_next_line(STDIN_FILENO, &buff) <= 0)
			break ;
		if (check_str(lemin, buff))
			break ;
	}
	if (lemin->node_count < 2 || lemin->link_count < 1 || lemin->ant_count < 0)
		error_msg("ERROR\n");
	fill_names(lemin);
}

t_lemin	*init_lemin(void)
{
	t_lemin	*lemin;

	check_malloc(lemin = (t_lemin*)malloc(sizeof(t_lemin)));
	lemin->part = 0;
	lemin->comment = 0;
	lemin->node_count = 0;
	lemin->link_count = 0;
	lemin->ant_count = 0;
	lemin->start = 0;
	lemin->end = 0;
	lemin->start_index = 0;
	lemin->end_index = 0;
	lemin->paths = NULL;
	lemin->fastest = NULL;
	lemin->visited = NULL;
	lemin->edges = NULL;
	lemin->names = NULL;
	lemin->ants = NULL;
	lemin->nodes = NULL;
	lemin->start_node = NULL;
	lemin->end_node = NULL;
	return (lemin);
}

void	init_ants(t_lemin *lemin)
{
	t_ant	**ants;
	int		i;

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
		free(lemin->paths->path);
		free(lemin->paths);
		lemin->paths = path;
	}
	lemin->paths = NULL;
}

int		check_flow(t_lemin *lemin)
{
	t_path	*path;
	int		flow;

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
	if (path->path[node + 1]->ants && !path->path[node + 1]->end)
		return (0);
	path->path[node + 1]->ants++;
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

void	step(t_lemin *lemin)
{
	int	i;
	int	end;
	int	flag;

	end = 0;
	while (!end)
	{
		flag = 0;
		end = 1;
		i = 0;
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
	int	i;
	int	j;
	t_path	*path;

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

int		main(void)
{
	t_lemin	*lemin;

	lemin = init_lemin();
	read_map(lemin);
	init_ants(lemin);
	max_flow(lemin, 0);
	cycle(lemin);
}
