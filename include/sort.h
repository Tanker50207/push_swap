/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 15:02:41 by gcrepin           #+#    #+#             */
/*   Updated: 2023/12/06 15:02:49 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SORT_H
# define SORT_H

# include "push_swap.h"

typedef enum e_call
{
	NEXT,
	PREV,
	NONE
}	t_call;

t_action	*roadtrip_sort(t_action *lst, t_stack *a, t_stack *b);
int			check_unordered(t_stack *stack);
int			check_sorted(t_stack a);
int			find_lowest(t_stack stack);
int			find_next(t_stack a, int i);
int			find_prev(t_stack a);
t_action	*road_push(t_action *lst, t_stack *a, t_stack *b, t_action act);
t_action	*road_rotate(t_action *lst, t_stack *a);

#endif
