/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 07:09:40 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/17 11:44:47 by vellery-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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
	int	i;

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
	char	**tmp;
	int		i;

	tmp = *split;
	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

int		coord_check(t_v2 loc, char **split)
{
	if (loc.x == ft_atoi(split[1]) && loc.y == ft_atoi(split[2]))
		return (1);
	return (0);
}
