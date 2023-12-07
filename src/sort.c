/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:36:31 by gcrepin           #+#    #+#             */
/*   Updated: 2023/12/05 15:08:46 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

static t_action	*push_back(t_action *lst, t_stack *a, t_stack *b)
{
	if (!lst)
		return (NULL);
	while (b->size > 0)
	{
		push(a, b);
		lst = add_action(lst, PA);
	}
	return (lst);
}

static t_action	*radix(t_action *lst, t_stack a, t_stack b)
{
	long	i;
	int		j;

	i = 1;
	while (lst && !check_sorted(a))
	{
		j = 0;
		while (lst && j < a.size && !check_sorted(a))
		{
			if (((long)a.tab[0] / i) % 2 == 0)
			{
				push(&b, &a);
				lst = add_action(lst, PB);
			}
			else
			{
				rotate(&a);
				lst = add_action(lst, RA);
				j++;
			}
		}
		lst = push_back(lst, &a, &b);
		i *= 2;
	}
	return (lst);
}

t_action	*sort(t_stack a, t_stack b)
{
	t_action	*actions;

	actions = (t_action *)malloc(sizeof(t_action));
	if (!actions)
		return (NULL);
	actions[0] = STOP;
	if (a.size_max <= 30)
		actions = roadtrip_sort(actions, &a, &b);
	else
		actions = radix(actions, a, b);
	return (actions);
}
