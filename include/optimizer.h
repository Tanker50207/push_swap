/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:39:17 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/20 13:39:28 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTIMIZER_H
# define OPTIMIZER_H

# include "push_swap.h"

t_action	*replace_one(t_action *lst, int i, int size, t_action replace);
t_action	*cleanup(t_action *lst);
t_action	*start_naive_optimize(t_action *lst);
t_action	*lst_dup(t_action *lst);
int			lst_compare(t_action *lst_a, t_action *lst_b);

#endif
