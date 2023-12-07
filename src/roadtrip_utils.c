/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roadtrip_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 16:40:37 by gcrepin           #+#    #+#             */
/*   Updated: 2023/12/06 16:40:42 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sort.h"

t_action	*road_push(t_action *lst, t_stack *a, t_stack *b,	t_action act)
{
	if (!lst)
		return (NULL);
	if (act == PA)
	{
		push(a, b);
		return (add_action(lst, PA));
	}
	push(b, a);
	return (add_action(lst, PB));
}

t_action	*road_rotate(t_action *lst, t_stack *a)
{
	if (!lst)
		return (NULL);
	rotate(a);
	return (add_action(lst, RA));
}
