/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roadtrip_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:40:51 by gcrepin           #+#    #+#             */
/*   Updated: 2023/12/06 14:40:59 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

static int	update_dest(t_stack a, t_stack b, int address, t_call call)
{
	int	ret;

	push(&a, &b);
	if (call == NEXT)
		ret = find_next(a, 0) + address;
	else
		ret = find_prev(a) + address + 1;
	push(&b, &a);
	return (ret);
}

static t_call	get_call(t_stack a, int ult, int address)
{
	int	prev_i;
	int	next_i;

	prev_i = find_prev(a) + address + 1;
	next_i = find_next(a, 0) + address;
	if (prev_i == -1 && next_i == -1)
		return (NONE);
	if (prev_i == -1 && next_i <= ult)
		return (NEXT);
	if (next_i == -1 && prev_i <= ult)
		return (PREV);
	if (prev_i > next_i && prev_i <= ult)
		return (PREV);
	if (next_i >= prev_i && next_i <= ult)
		return (NEXT);
	return (NONE);
}

static t_action	*start_trip(t_action *lst, t_stack *a, t_stack *b, int ult)
{
	static int	address = 0;
	int			destination;
	t_call		call;

	address = (address + 1) * (b->size != 0);
	if (ult == address)
		return (lst);
	call = get_call(*a, ult, address);
	if (call != NONE)
	{
		lst = road_push(lst, a, b, PB);
		destination = update_dest(*a, *b, address, call);
		while (lst && destination - 1 > address)
		{
			lst = start_trip(lst, a, b, destination);
			destination = update_dest(*a, *b, address, call);
			if (destination > ult)
				break ;
		}
		lst = road_push(lst, a, b, PA);
	}
	else
		lst = road_rotate(lst, a);
	return (lst);
}

t_action	*roadtrip_sort(t_action *lst, t_stack *a, t_stack *b)
{
	if (!lst)
		return (NULL);
	while (lst && find_lowest(*a) != 0)
		lst = start_trip(lst, a, b, find_lowest(*a));
	while (lst && !check_unordered(a))
		lst = start_trip(lst, a, b, a->size_max);
	while (lst && !check_sorted(*a))
		lst = road_rotate(lst, a);
	return (lst);
}
