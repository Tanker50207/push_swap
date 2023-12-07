/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_optimizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 15:11:17 by gcrepin           #+#    #+#             */
/*   Updated: 2023/12/04 15:11:28 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizer.h"

static t_action	*swap_opt(t_action *lst, int i)
{
	if (lst[i] == PB && lst[i + 1] == RRA && lst[i + 2] == PA)
	{
		lst = replace_one(lst, i, 3, RRA);
		lst[i + 1] = SA;
	}
	else if (lst[i] == PA && lst[i + 1] == RRB && lst[i + 2] == PB)
	{
		lst = replace_one(lst, i, 3, RRB);
		lst[i + 1] = SB;
	}
	else if (lst[i] == PB && lst[i + 1] == RA && lst[i + 2] == PA)
	{
		lst = replace_one(lst, i, 3, SA);
		lst[i + 1] = RA;
	}
	else if (lst[i] == PA && lst[i + 1] == RB && lst[i + 2] == PB)
	{
		lst = replace_one(lst, i, 3, SB);
		lst[i + 1] = RB;
	}
	return (lst);
}

t_action	*find_best_swap(t_action *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (NULL);
	if (lst[0] == STOP || lst[1] == STOP)
		return (lst);
	while (lst[i + 2] != STOP)
		lst = swap_opt(lst, i++);
	return (lst);
}
