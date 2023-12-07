/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 12:23:49 by gcrepin           #+#    #+#             */
/*   Updated: 2023/12/03 12:24:00 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	exec_action_2(t_action action, t_stack *a, t_stack *b)
{
	if (action == SS)
	{
		swap(a);
		swap(b);
	}
	else if (action == RR)
	{
		rotate(a);
		rotate(b);
	}
	else if (action == RRR)
	{
		reverse_rotate(a);
		reverse_rotate(b);
	}
}

void	exec_action(t_action action, t_stack *a, t_stack *b)
{
	if (action == SA)
		swap(a);
	else if (action == SB)
		swap(b);
	else if (action == PA)
		push(a, b);
	else if (action == PB)
		push(b, a);
	else if (action == RA)
		rotate(a);
	else if (action == RB)
		rotate(b);
	else if (action == RRA)
		reverse_rotate(a);
	else if (action == RRB)
		reverse_rotate(b);
	else
		exec_action_2(action, a, b);
}
