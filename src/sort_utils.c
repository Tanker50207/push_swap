/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:08:59 by gcrepin           #+#    #+#             */
/*   Updated: 2023/12/06 15:09:04 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

int	find_lowest(t_stack stack)
{
	int	i;
	int	index;

	i = 0;
	index = i;
	while (i < stack.size)
	{
		if (stack.tab[i] < stack.tab[index])
			index = i;
		i++;
	}
	return (index);
}

int	find_next(t_stack a, int i)
{
	int	hold;
	int	next_i;
	int	cur;

	hold = i;
	cur = a.tab[i];
	next_i = -1;
	while (i < a.size)
	{
		if (a.tab[i] > cur && (next_i == -1 || a.tab[i] < a.tab[next_i]))
			next_i = i;
		i++;
	}
	if (next_i == hold + 1)
		return (find_next(a, next_i));
	return (next_i);
}

int	find_prev(t_stack a)
{
	int	prev_i;
	int	cur;
	int	i;

	cur = a.tab[0];
	prev_i = -1;
	i = 0;
	while (i < a.size)
	{
		if (a.tab[i] < cur && (prev_i == -1 || a.tab[i] > a.tab[prev_i]))
			prev_i = i;
		i++;
	}
	return (prev_i);
}

int	check_sorted(t_stack stack)
{
	int	i;

	i = 0;
	while (i < stack.size - 1)
	{
		if (stack.tab[i] > stack.tab[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	check_unordered(t_stack *stack)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	while (i < stack->size - 1 && err < 2)
	{
		if (stack->tab[i] > stack->tab[i + 1])
			err++;
		i++;
	}
	if (stack->tab[i] > stack->tab[0])
		err++;
	if (err > 1)
		return (0);
	return (1);
}
