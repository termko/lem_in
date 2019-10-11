/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 18:11:05 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/11 07:49:19 by ydavis           ###   ########.fr       */
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
	int	**arr;

	check_malloc(arr = (int**)malloc(sizeof(int*) * lemin->node_count));
	i = 0;
	while (i < lemin->node_count)
	{
		check_malloc(arr[i] = (int*)malloc(sizeof(int) * lemin->node_count));
		ft_bzero(arr[i], lemin->node_count * sizeof(int));
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
		i++;
		tmp = tmp->next;
	}
	lemin->names[i] = NULL;
}

void	read_map(t_lemin *lemin)
{
	char	*buff;
	int		i;

	i = 0;
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
		ants[i]->curr_node = lemin->start_node;
		ants[i]->next_node = NULL;
		ants[i]->at_end = 0;
		i++;
	}
	ants[i] = NULL;
	lemin->ants = ants;
}

t_stack	*new_stack(int cap)
{
	t_stack	*ret;

	check_malloc(ret = malloc(sizeof(t_stack) + cap * sizeof(int)));
	ret->cap = cap;
	ret->start = 0;
	ret->size = 0;
	return (ret);
}

void	st_push(t_stack *stack, int x)
{
	if (stack->size >= stack->cap)
		return ;
	stack->store[(stack->start + stack->size) % stack->cap] = x;
	stack->size++;
}

int		st_pop(t_stack *stack)
{
	int	x;

	if (!stack->size)
		return (-1);
	x = stack->store[stack->start];
	stack->start++;
	stack->size--;
	return (x);
}

void	del_stack(t_stack **stack)
{
	free(*stack);
	*stack = NULL;
}

int		count_backtrack(t_lemin *lemin, int i)
{
	int	count;
	int	start;

	start = index_of_node(lemin, lemin->start_node->name);
	count = 1;
	while (i != start)
	{
		count++;
		i = lemin->edges[i][i] - 1;
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

t_node	**backtrack(t_lemin *lemin, t_stack **stack, int i)
{
	t_node	**path;
	int		count;
	int		j;
	int		prev;

	del_stack(stack);
	count = count_backtrack(lemin, i);
	check_malloc(path = (t_node**)malloc(sizeof(t_node*) * (count + 1)));
	j = 0;
	while (j < count - 2)
	{
		prev = lemin->edges[i][i] - 1;
		if ((find_node(lemin, lemin->names[prev]))->start)
			return (path);
		check_malloc(path[j] = find_node(lemin, lemin->names[prev]));
		clear_prev(lemin, prev, i);
		i = prev;
	}
	return (path);
}

t_node	**bfs(t_lemin *lemin, t_stack *stack, int i)
{
	int		j;
	int		x;

	j = 0;
	while (j < lemin->node_count)
	{
		if (i != j && lemin->edges[i][j] > 0 && !lemin->visited[j])
		{
			lemin->edges[j][j] = i + 1;
			if (!ft_strcmp(lemin->names[j], lemin->end_node->name))
				return (backtrack(lemin, &stack, i));
			lemin->visited[j] = 1;
			st_push(stack, j);
		}
		j++;
	}
	if (stack->size == 0)
		return (NULL);
	x = st_pop(stack);
	return (bfs(lemin, stack, x));
}

void	max_flow(t_lemin *lemin)
{
	t_node	**path;
	t_stack	*stack;
	int		ind;

	path = NULL;
	check_malloc(stack = new_stack(lemin->node_count));
	if (!lemin->visited)
		check_malloc(lemin->visited = (int*)malloc(sizeof(int) * lemin->node_count));
	ft_bzero(lemin->visited, sizeof(int) * lemin->node_count);
	ind = index_of_node(lemin, lemin->start_node->name);
	lemin->visited[ind] = 1;
	path = bfs(lemin, stack, ind);
	int i;
	i = 0;
	while (path[i])
	{
		printf("%s\n", path[i]->name);
		i++;
	}
}

int		main(void)
{
	t_lemin	*lemin;

	lemin = init_lemin();
	read_map(lemin);
	init_ants(lemin);
	max_flow(lemin);
//	cycle(lemin);
}
