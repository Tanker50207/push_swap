/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:12:14 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/22 16:47:34 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "simulator.h"

static t_stack	s_execute(t_action action, t_stack stack)
{
	if (action == RA)
		rotate(&stack);
	else if (action == RRA)
		reverse_rotate(&stack);
	else if (action == SA)
		swap(&stack);
	return (stack);
}

t_stack	*generate_scenario(int scenario)
{
	t_stack	*stack;
	int		i;

	stack = innit_stack(6);
	i = 0;
	while (i < 6)
	{
		stack->tab[i] = scenario % 10;
		scenario /= 10;
		i++;
	}
	return (stack);
}

t_action	*action_tree(t_stack stack)
{
	t_action	*temp;
	static int	depth = 0;

	depth++;
	if (depth > 5)
	{
		depth--;
		return (NULL);
	}
	if (check_sorted(stack))
		return (add_action(NULL, STOP));
	temp = action_tree(s_execute(RA, stack));
	if (temp)
		return (add_action(temp, RRA));
	temp = action_tree(s_execute(RRA, stack));
	if (temp)
		return (add_action(temp, RA));
	temp = action_tree(s_execute(SA, stack));
	if (temp)
		return (add_action(temp, SA));
	depth--;
	return (NULL);
}

int	is_valid_scenario(t_stack stack)
{
	int	i;
	int	j;

	i = 0;
	while (i < stack.size - 1)
	{
		j = i + 1;
		while (j < stack.size)
		{
			if (stack.tab[i] == stack.tab[j] || stack.tab[i] > 5
				|| stack.tab[j] > 5)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_action	*find_optimal(int scenario)
{
	t_stack		*stack;
	t_action	*retval;

	stack = generate_scenario(scenario);
	if (!stack)
		return (NULL);
	if (!is_valid_scenario(*stack))
	{
		free_stack(stack);
		return (NULL);
	}
	retval = action_tree(*stack);
	if (!retval)
		return (NULL);
	free_stack(stack);
	return (retval);
}

