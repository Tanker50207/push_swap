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

t_action	*optimize(t_action *lst, t_stack a, t_stack b)
{
	lst = start_naive_optimize(lst);
	return (lst);
}
