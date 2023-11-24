/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 11:36:31 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/24 15:45:13 by gcrepin          ###   ########.fr       */
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

static int find_prev(t_stack a)
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
	prev_i = find_prev(*a);
	next_i = find_next(*a, 0);
//	ft_printf("prev_i = %d, next_i = %d\n", prev_i, next_i);
	index = 0;
	if (prev_i == -1 && next_i == -1)
		return (lst);
	if ((prev_i == -1 && next_i + depth <= ult)
		|| (next_i != -1 && next_i + depth <= ult && next_i < prev_i))
	{
		push(b, a);
		lst = add_action(lst, PB);
		index = next_i + depth;
		prev_i = -1;
	}
	else if (prev_i != -1 && prev_i + depth + 1 < ult)
	{
		push(b, a);
		lst = add_action(lst, PB);
		index = prev_i + depth + 1;
		next_i = -1;
	}
	if (index)
	{
		while (index - (prev_i == -1) != depth)
//		while (index != depth)
			lst = join_r(lst, a, b, index);
		push(a, b);
		lst = add_action(lst, PA);
		if (prev_i != -1 && prev_i + depth < ult)
			depth--;
	}
	if (index && next_i != -1)
//	if (index && b->tab[0] > a->tab[find_prev(*a)] && b->tab[0] < a->tab[0] && next_i != -1)
		(void) 0;
	else
	{
		lst = add_action(lst, RA);
		rotate(a);
	}
	return (lst);
}

static t_action	*join(t_action *lst, t_stack *a, t_stack *b)
{
	int			prev_i;
	int			next_i;
	int			destination;
	t_action	direction;

	prev_i = find_prev(*a);
	next_i = find_next(*a, 0);
	if (prev_i == -1 && next_i == -1)
		return (lst);
	if (prev_i == -1 || (next_i < a->size / 2 && next_i < prev_i)
		|| (next_i > a->size / 2 && next_i > prev_i))
		destination = next_i;
	else
		destination = prev_i + 1;
	if (destination == a->size)
		return (lst);
	if (destination < a->size / 2)
		direction = RA;
	else
		direction = RRA;
	push(b, a);
	lst = add_action(lst, PB);
	return (lst);
} //TODO: Fix this

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
	while (!check_unnordered(a))
	{
		lst = join_r(lst, a, b, a->size);
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
