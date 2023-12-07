/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_optimizer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 11:59:04 by gcrepin           #+#    #+#             */
/*   Updated: 2023/12/03 11:59:25 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizer.h"

static t_action	*find_best_rotation(t_action *lst, size_t i, int stack_size)
{
	size_t	j;
	int		rotation;

	j = i;
	rotation = 0;
	while (lst[j] == RA || lst[j] == RRA)
	{
		if (lst[j] == RA)
			rotation++;
		else if (lst[j] == RRA)
			rotation--;
		j++;
	}
	rotation = (stack_size + (rotation % stack_size)) % stack_size;
	lst = replace_one(lst, i, j - i, DEL);
	if (rotation <= stack_size / 2)
		while (rotation--)
			lst[i++] = RA;
	else
		while (rotation++ < stack_size)
			lst[i++] = RRA;
	return (lst);
}

t_action	*rotation_optimizer(t_action *lst, t_stack a, t_stack b)
{
	size_t	i;

	i = 0;
	if (!lst)
		return (NULL);
	while (i < lst_size(lst))
	{
		if (lst[i] == RA || lst[i] == RRA)
			lst = find_best_rotation(lst, i, a.size);
		else if (lst[i] == RB || lst[i] == RRB)
			lst = find_best_rotation(lst, i, b.size);
		exec_action(lst[i], &a, &b);
		i++;
	}
	return (lst);
}
