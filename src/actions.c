/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:51:05 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/15 16:16:32 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*push(t_stack *dest_stack, t_stack *src_stack)
{
	int	i;

	if (!src_stack || !dest_stack)
		return (dest_stack);
	i = dest_stack->size_max - 1;
	while (i > 0)
	{
		dest_stack->tab[i] = dest_stack->tab[i - 1];
		i--;
	}
	dest_stack->tab[0] = src_stack->tab[0];
	i = 0;
	while (i < src_stack->size_max - 1)
	{
		src_stack->tab[i] = src_stack->tab[i + 1];
		i++;
	}
	src_stack->tab[i] = 0;
	dest_stack->size++;
	src_stack->size--;
	return (dest_stack);
}

t_stack	*swap(t_stack *stack)
{
	int	tmp;

	tmp = stack->tab[0];
	stack->tab[0] = stack->tab[1];
	stack->tab[1] = tmp;
	return (stack);
}

t_stack	*rotate(t_stack *stack)
{
	int	i;
	int	tmp;

	i = 0;
	tmp = stack->tab[0];
	while (i < stack->size - 1)
	{
		stack->tab[i] = stack->tab[i + 1];
		i++;
	}
	stack->tab[i] = tmp;
	return (stack);
}

t_stack	*reverse_rotate(t_stack *stack)
{
	int	i;
	int	tmp;

	i = stack->size - 1;
	tmp = stack->tab[i];
	while (i > 0)
	{
		stack->tab[i] = stack->tab[i - 1];
		i--;
	}
	stack->tab[i] = tmp;
	return (stack);
}

t_action	*add_action(t_action *lst, t_action action)
{
	int	i;

	i = 0;
	while (lst[i] != STOP)
		i++;
	lst = (t_action *)ft_realloc(lst, sizeof(t_action) * (i + 2));
	if (!lst)
		return (NULL);
	lst[i] = action;
	lst[i + 1] = STOP;
//	switch (action)
//	{
//		case SA:
//			ft_printf("sa\n");
//			break;
//		case SB:
//			ft_printf("sb\n");
//			break;
//		case PA:
//			ft_printf("pa\n");
//			break;
//		case PB:
//			ft_printf("pb\n");
//			break;
//		case RA:
//			ft_printf("ra\n");
//			break;
//		case RB:
//			ft_printf("rb\n");
//			break;
//		case RRA:
//			ft_printf("rra\n");
//			break;
//		case RRB:
//			ft_printf("rrb\n");
//			break;
//		default:
//			break;
//	}
	return (lst);
}
