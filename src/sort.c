/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:36:31 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/16 12:36:52 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "push_swap.h"

//static t_action	*push_back(t_action *lst, t_stack *a, t_stack *b)
//{
//	while (b->size > 0)
//	{
//		push(a, b);
//		lst = add_action(lst, PA);
//	}
//	return (lst);
//}

//DEBUG
__attribute__((unused)) void	print_stack(t_stack stack)
{
	int	i;

	i = 0;
	while (i < stack.size)
	{
		ft_putnbr(stack.tab[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putchar_fd('\n', 1);
}

int	check_sorted(t_stack stack_a, t_stack stack_b)
{
	int	i;

	i = 0;
	while (i < stack_a.size - 1)
	{
		if (stack_a.tab[i] > stack_a.tab[i + 1])
			return (0);
		i++;
	}
	i = 0;
	while (i < stack_b.size - 1)
	{
		if (stack_b.tab[i] < stack_b.tab[i + 1])
			return (0);
		i++;
	}
	return (1);
}

int	check_unnordered(t_stack *stack)
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

//static t_action	*radix(t_action *lst, t_stack a, t_stack b)
//{
//	long	i;
//	int		j;
//
//	i = 1;
//	while (!check_sorted(a, b))
//	{
//		j = 0;
//		while (j < a.size && !check_sorted(a, b))
//		{
//			if (((long)a.tab[0] / i) % 2 == 0)
//			{
//				push(&b, &a);
//				lst = add_action(lst, PB);
//			}
//			else
//			{
//				rotate(&a);
//				lst = add_action(lst, RA);
//				j++;
//			}
//		}
//		lst = push_back(lst, &a, &b);
//		i *= 2;
//	}
//	return (lst);
//}

static t_action	*join(t_action	*lst,int h_index,int l_index,
						 t_stack *a)
{
	int	i;

	i = 0;
	while (i++ < l_index)
	{
		lst = add_action(lst, RA);
		rotate(a);
	}
	if (i == a-> size)
		i = 0;
	while (i++ != h_index)
	{
		if (i == a->size)
			i = 0;
		lst = add_action(lst, SA);
		swap(a);
//		if (i != h_index)
//		{
			lst = add_action(lst, RA);
			rotate(a);
//		}
	}
	return (lst);
}

static int	find_next_highest(t_stack a, int high)
{
	int	i;
	int	index;

	i = 0;
	while (high != -1 && a.tab[i] >= high)
		i++;
	index = i;
	while (i < a.size)
	{
		if (a.tab[i] > a.tab[index] && (high == -1 || a.tab[i] < high))
			index = i;
		i++;
	}
	return (index);
}

static t_action	*my_sort(t_action *lst, t_stack *a, t_stack *b)
{
	int	current;
	int	to_join;

	(void)b;
	current = find_next_highest(*a, -1);
	while (!check_unnordered(a))
	{
		to_join = find_next_highest(*a, a->tab[current]);
		lst = join(lst, current, to_join, a);
		current = 0;
//		print_stack(*a);
	}
	while (!check_sorted(*a, *b))
	{
		lst = add_action(lst, RA);
		rotate(a);
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
//	actions = radix(actions, a, b);
	actions = my_sort(actions, &a, &b);
	return (actions);
}
