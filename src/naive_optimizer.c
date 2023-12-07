/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   naive_optimizer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:55:20 by gcrepin           #+#    #+#             */
/*   Updated: 2023/12/07 12:25:09 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizer.h"

static int	is_nullable(t_action a, t_action b)
{
	if ((a == RA && b == RRA) || (a == RRA && b == RA)
		|| (a == RB && b == RRB) || (a == RRB && b == RB))
		return (1);
	if ((a == SA && b == SA) || (a == SB && b == SB))
		return (1);
	if ((a == PA && b == PB) || (a == PB && b == PA))
		return (1);
	return (0);
}

t_action	*naive_prs_optimize(t_action *lst)
{
	size_t	i;
	size_t	s;

	i = 0;
	while (lst && lst[i] != STOP)
	{
		s = i;
		while (lst[s] == RA || lst[s] == RRA
			|| lst[s] == RB || lst[s] == RRB)
		{
			if (is_nullable(lst[i], lst[s]))
			{
				lst[i] = DEL;
				lst[s] = DEL;
				break ;
			}
			s++;
		}
		if (is_nullable(lst[i], lst[i + 1]))
			lst = replace_one(lst, i, 2, DEL);
		i++;
	}
	lst = cleanup(lst);
	return (lst);
}
