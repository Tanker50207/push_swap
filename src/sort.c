/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:36:31 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/24 16:36:51 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_action	*push_back(t_action *lst, t_stack *a, t_stack *b)
{
	while (b->size > 0)
	{
		push(a, b);
		lst = add_action(lst, PA);
	}
	return (lst);
}

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

static t_action	*radix(t_action *lst, t_stack a, t_stack b)
{
	long	i;
	int		j;

	i = 1;
	while (!check_sorted(a))
	{
		j = 0;
		while (j < a.size && !check_sorted(a))
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

static t_action	*n_join(t_action	*lst, int h_index, int l_index,
						t_stack *a)
{
	int	i;

	i = 0;
	while (i++ < l_index)
	{
		lst = add_action(lst, RA);
		rotate(a);
	}
	if (i == a->size)
		i = 0;
	while (i++ != h_index)
	{
		if (i == a->size)
			i = 0;
		lst = add_action(lst, SA);
		swap(a);
		lst = add_action(lst, RA);
		rotate(a);
	}
	return (lst);
}

static int	find_lowest(t_stack stack)
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

static int	find_next(t_stack a, int i)
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

static int find_prev(t_stack a, int cur)
{
	int	prev_i;
	int	i;

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

static t_action	*join_r(t_action * lst, t_stack *a, t_stack *b, int ult)
{
	static int	depth = -1;
	int			prev_i;
	int			next_i;
	int			index;

	if (b->size == 0)
		depth = -1;
	depth++;
//	ft_printf("ult = %d, depth = %d\n", ult, depth);
	if (ult == depth)
		return (lst);
//	if (depth > ult || depth > a->size_max || ult > a->size_max)
//		ft_printf("depth = %d, ult = %d\n", depth, ult);
	if (depth > ult + 50)
		exit(EXIT_FAILURE);
	prev_i = find_prev(*a, a->tab[0]);
	if (prev_i != -1)
		prev_i++;
	next_i = find_next(*a, 0);
//	ft_printf("prev_i = %d, next_i = %d\n", prev_i, next_i);
	index = 0;
	if (prev_i == -1 && next_i == -1)
		return (lst);
	if ((prev_i == -1 && next_i + depth <= ult)
		|| (next_i != -1 && next_i + depth <= ult && next_i <= prev_i))
	{
		push(b, a);
		lst = add_action(lst, PB);
//		ft_printf("next\n");
		index = next_i + depth;
		prev_i = -1;
	}
	else if (prev_i != -1 && prev_i + depth <= ult && prev_i < next_i)
	{
//		ft_printf("prev_i = %d, depth = %d, ult = %d\n", prev_i, depth, ult);
		push(b, a);
		lst = add_action(lst, PB);
//		ft_printf("prev\n");
		index = prev_i + depth;
		next_i = -1;
	}
	if (index)
	{
//		ft_printf("sending to depth %d\n", index - (prev_i == -1));
		while (index - 1 != depth)
		{
			lst = join_r(lst, a, b, index);
			if (next_i == -1)
			{
				index = find_prev(*a, b->tab[0]) + depth + 1;
				if (index > a->size)
				{
//					ft_printf("revised absolute index = %d\n", index);
//					ft_printf("revised relative index = %d\n", index - depth - 1);
				}
				if (find_prev(*a, b->tab[0]) == a->size - 1)
				{
					lst = add_action(lst, RRA);
					reverse_rotate(a);
					index = depth;
					depth--;
					break ;
				}
			}
		}
		if (next_i == -1)
		{
			lst = add_action(lst, RA);
			rotate(a);
			depth++;
//			if (find_prev(*a, b->tab[0]) == 0)
//			{
//				ft_printf("WHY? depth = %d, ult = %d, index = %d\n", depth, ult, index);
//			}
		}
		push(a, b);
		lst = add_action(lst, PA);
//		if (next_i == -1 && find_prev(*a, a->tab[0]) == a->size - 1)
//			depth--;
//		if (prev_i != -1 && prev_i + depth < ult)
//			depth--;
	}
//	if (index && next_i != -1)
	if (index && prev_i != -1 && find_prev(*a, b->tab[0]) == a->size - 1)
	{
//		ft_printf("YOU SHALL NOT ROTATE!\n reason: ");
//		if (b->tab[0] > a->tab[find_prev(*a, a->tab[0])] && b->tab[0] < a->tab[0])
//			ft_printf("b[0] = %d > a[prev] = %d && b[0] = %d < a[0] = %d\n", b->tab[0], a->tab[find_prev(*a, a->tab[0])], b->tab[0], a->tab[0]);
//		else
//			ft_printf("find_prev(*a, b->tab[0]) = %d == a->size - 1 = %d\n", find_prev(*a, b->tab[0]), a->size - 1);
		depth--;
	}
	else if (!(index && next_i == -1))
	{
		lst = add_action(lst, RA);
		rotate(a);
	}
	return (lst);
}

static t_action	*n_sort(t_action *lst,t_stack *a,t_stack *b)
{
	int	current;
	int	to_join;

	(void)b;
	current = find_next_highest(*a, -1);
	while (!check_unnordered(a))
	{
		to_join = find_next_highest(*a, a->tab[current]);
		lst = n_join(lst,current,to_join,a);
		current = 0;
//		print_stack(*a);
	}
	while (!check_sorted(*a))
	{
		lst = add_action(lst, RA);
		rotate(a);
	}
	return (lst);
}

static t_action	*my_sort(t_action *lst, t_stack *a, t_stack *b)
{
	while (find_lowest(*a) != 0)
	{
		lst = join_r(lst, a, b, find_lowest(*a));
//		lst = add_action(lst, DEBUG);
		if (find_lowest(*a) != 0)
		{
			lst = add_action(lst, RA);
			rotate(a);
		}
	}
	while (!check_unnordered(a))
	{
//		if (find_lowest(*a) != 0)
//		{
//			lst = add_action(lst, RRA);
//			reverse_rotate(a);
//		}
		if (find_prev(*a, a->tab[0]) == a->size - 1)
		{
			lst = add_action(lst, RRA);
			reverse_rotate(a);
		}
		lst = join_r(lst, a, b, a->size);
//		lst = add_action(lst, DEBUG);
		lst = optimize(lst, *a, *b);
	}
	while (!check_sorted(*a))
	{
		lst = add_action(lst, RRA);
		reverse_rotate(a);
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
//	actions = n_sort(actions,&a,&b);
	actions = my_sort(actions, &a, &b);
	return (actions);
}
