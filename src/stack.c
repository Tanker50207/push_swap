/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 11:42:55 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/15 11:43:01 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*innit_stack(int size)
{
	t_stack	*stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	stack->tab = (int *)ft_calloc(size, sizeof(int));
	if (!stack->tab)
		return (NULL);
	stack->size_max = size;
	stack->size = 0;
	return (stack);
}

void	free_stack(t_stack *stack)
{
	if (!stack)
		return ;
	if (stack->tab)
		free(stack->tab);
	free(stack);
}
