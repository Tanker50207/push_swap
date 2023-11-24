/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dict_maker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 16:39:36 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/22 16:39:41 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_action	*find_optimal(int scenario);

t_action	**make_optimal_dict(void)
{
	t_action	**lst;
	int			i;

	lst = (t_action **)malloc(sizeof(t_action *) * 1000000);
}