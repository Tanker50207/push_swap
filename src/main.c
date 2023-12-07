/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:40:07 by gcrepin           #+#    #+#             */
/*   Updated: 2023/12/06 14:30:26 by gcrepin          ###   ########.fr       */
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
	if (has_dup(tab, i))
	{
		free(tab);
		return (NULL);
	}
	tab = sanitize_int_tab(tab, i);
	return (tab);
}

int	free_all_stacks(t_stack *a, t_stack *b, int *tab)
{
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	if (tab)
		free(tab);
	return (0);
}

static void	print_actions(const t_action *actions)
{
	size_t	i;

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
		i++;
	}
}

static int	*get_tab(int *argc, char **argv)
{
	char	**hold;
	int		i;
	int		*ret;

	if (*argc != 2)
		return (to_int_tab(argv + 1));
	hold = ft_split(argv[1], ' ');
	if (!hold)
		return (NULL);
	i = 0;
	while (hold[i])
		i++;
	*argc = i + 1;
	ret = to_int_tab(hold);
	while (i)
		free(hold[--i]);
	free(hold);
	return (ret);
}

int	main(int argc, char **argv)
{
	t_stack		*a;
	t_stack		*b;
	t_action	*actions;
	int			*tab;

	if (argc == 1)
		error();
	tab = get_tab(&argc, argv);
	a = innit_stack(argc - 1);
	b = innit_stack(argc - 1);
	if (!a || !b || !tab)
		error_and_free(a, b, tab);
	free(a->tab);
	a->tab = tab;
	a->size = a->size_max;
	actions = sort(*a, *b);
	actions = optimize(actions, *a, *b);
	print_actions(actions);
	if (!actions)
		error_and_free(a, b, tab);
	free_all_stacks(a, b, tab);
	return (0);
}
