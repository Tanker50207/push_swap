/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:53:25 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/21 12:53:31 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizer.h"

size_t	lst_size(const t_action *lst)
{
	size_t	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst[i] != STOP)
		i++;
	return (i);
}

t_action	*optimize(t_action *lst, t_stack a, t_stack b)
{
	t_action	*dup;

	dup = 0;
	while (lst && !lst_compare(lst, dup))
	{
		if (dup)
			free(dup);
		dup = lst_dup(lst);
		if (!dup)
			return (NULL);
		lst = naive_prs_optimize(lst);
		lst = rotation_optimizer(lst, a, b);
		lst = find_best_swap(lst);
		lst = cleanup(lst);
	}
	if (dup)
		free(dup);
	return (lst);
}
