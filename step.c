/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydavis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:29:27 by ydavis            #+#    #+#             */
/*   Updated: 2019/10/17 13:35:43 by ydavis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int		step_cycle(t_lemin *lemin, int *first, int i)
{
	int		flag;
	int		end;

	end = 1;
	flag = 0;
	while (i < lemin->ant_count)
	{
		if (!flag)
			*first = i;
		if (!lemin->ants[i]->at_end)
		{
			if (ant_step(lemin, i, flag))
			{
				flag = 1;
				end = 0;
			}
			else
				break ;
		}
		i++;
	}
	return (end);
}
