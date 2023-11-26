/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:40:07 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/24 16:38:01 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	*to_int_tab(char **argv)
{
	int	*tab;
	int	i;

	i = 0;
	while (argv[i])
		i++;
	tab = (int *)malloc(sizeof(int) * i);
	if (!tab)
		return (NULL);
	i = 0;
	while (argv[i])
	{
		tab[i] = ft_atoi(argv[i]);
		i++;
	}
	return (tab);
}

static int	free_all_stacks(t_stack *a, t_stack *b)
{
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	return (0);
}

static void	print_actions(const t_action *actions)
{
	int	i;

	i = 0;
	while (actions && actions[i] != STOP)
	{
		if (actions[i] == SA)
			ft_printf("sa\n");
		else if (actions[i] == SB)
			ft_printf("sb\n");
		else if (actions[i] == PA)
			ft_printf("pa\n");
		else if (actions[i] == PB)
			ft_printf("pb\n");
		else if (actions[i] == RA)
			ft_printf("ra\n");
		else if (actions[i] == RB)
			ft_printf("rb\n");
		else if (actions[i] == RRA)
			ft_printf("rra\n");
		else if (actions[i] == RRB)
			ft_printf("rrb\n");
		else if (actions[i] == DEBUG)
			ft_printf("debug\n");
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;
	t_action	*actions;

	if (argc == 1)
		return (0);
	a = innit_stack(argc - 1);
	b = innit_stack(argc - 1);
	if (!a || !b)
		return (free_all_stacks(a, b));
	if (a->tab)
		free(a->tab);
	a->tab = to_int_tab(argv + 1);
	if (!a->tab)
		return (free_all_stacks(a, b));
	a->size = a->size_max;
	actions = sort(*a, *b);
	actions = optimize(actions, *a, *b);
	print_actions(actions);
	free_all_stacks(a, b);
	if (actions)
		free(actions);
	return (0);
}
