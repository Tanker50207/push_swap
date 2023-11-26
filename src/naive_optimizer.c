/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:38:56 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/24 12:50:02 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "optimizer.h"

//t_action	*combine(t_action *lst)
//{
//	int	i;
//
//	i = 0;
//	while (lst && lst[i] != STOP)
//	{
//		if ((lst[i] == SA && lst[i + 1] == SB)
//			|| (lst[i] == SB && lst[i + 1] == SA))
//			lst = replace_one(lst, i, 2, SS);
//		else if ((lst[i] == RA && lst[i + 1] == RB)
//				 || (lst[i] == RB && lst[i + 1] == RA))
//			lst = replace_one(lst, i, 2, RR);
//		else if ((lst[i] == RRA && lst[i + 1] == RRB)
//				 || (lst[i] == RRB && lst[i + 1] == RRA))
//			lst = replace_one(lst, i, 2, RRR);
//		i++;
//	}
//	return (lst);
//}

int	is_nullable(t_action a, t_action b)
{
	if ((a == RA && b == RRA) || (a == RRA && b == RA)
		|| (a == RB && b == RRB) || (a == RRB && b == RB))
		return (1);
	if ((a == SA && b == SA) || (a == SB && b == SB))
		return (1);
	if ((a == PA && b == PB) || (a == PB && b == PA))
		return (1);
	return (0);
}

t_action	*naive_prs_optimize(t_action *lst)
{
	int	i;
	int	s;

	i = 0;
	while (lst[i] != STOP)
	{
		s = i;
		while (lst[s] == RA || lst[s] == RRA
			|| lst[s] == RB || lst[s] == RRB)
		{
			if (is_nullable(lst[i], lst[s]))
			{
				lst[i] = DEL;
				lst[s] = DEL;
				break ;
			}
			s++;
		}
		if (is_nullable(lst[i], lst[i + 1]))
			lst = replace_one(lst, i, 2, DEL);
		i++;
	}
	lst = cleanup(lst);
	return (lst);
}

t_action	*start_naive_optimize(t_action *lst)
{
	t_action	*lst_ref;

	lst_ref = lst_dup(lst);
	if (!lst_ref)
	{
		free(lst);
		return (NULL);
	}
	lst = naive_prs_optimize(lst);
	while (!lst_compare(lst, lst_ref))
	{
		free(lst_ref);
		lst_ref = lst_dup(lst);
		if (!lst_ref)
		{
			free(lst);
			return (NULL);
		}
		lst = naive_prs_optimize(lst);
	}
	free(lst_ref);
	return (lst);
}
