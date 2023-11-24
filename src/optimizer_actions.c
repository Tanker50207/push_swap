/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizer_actions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 12:34:07 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/21 12:34:13 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizer.h"

t_action	*lst_dup(t_action *lst)
{
	int			i;
	t_action	*dup;

	i = 0;
	while (lst[i] != STOP)
		i++;
	dup = (t_action *)malloc(sizeof(t_action) * (i + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (lst[i] != STOP)
	{
		dup[i] = lst[i];
		i++;
	}
	dup[i] = STOP;
	return (dup);
}

int	lst_compare(t_action *lst_a, t_action *lst_b)
{
	int	i;

	i = 0;
	while (lst_a[i] != STOP && lst_b[i] != STOP)
	{
		if (lst_a[i] != lst_b[i])
			return (0);
		i++;
	}
	if (lst_a[i] != lst_b[i])
		return (0);
	return (1);
}

t_action	*replace_one(t_action *lst, int i, int size, t_action replace)
{
	int	j;

	lst[i] = replace;
	j = 1;
	while (j < size && lst[i + j] != STOP) //Second condition potentially redundant, but better be safe than sorry
		lst[i + j++] = DEL;
	return (lst);
}

t_action	*cleanup(t_action *lst)
{
	int	i;
	int	j;

	i = 0;
	while (lst[i] != STOP)
	{
		if (lst[i] == DEL)
		{
			j = i;
			while (lst[j] == DEL)
				j++;
			lst[i] = lst[j];
			lst[j] = DEL;
		}
		if (lst[i] == STOP)
			break ;
		i++;
	}
	return (lst);
}
