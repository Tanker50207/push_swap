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

t_action	*replace_one(t_action *lst, size_t i,
				size_t size, t_action replace);
t_action	*cleanup(t_action *lst);
t_action	*lst_dup(const t_action *lst);
t_action	*naive_prs_optimize(t_action *lst);
int			lst_compare(const t_action *lst_a, const t_action *lst_b);
size_t		lst_size(const t_action *lst);
t_action	*rotation_optimizer(t_action *lst, t_stack a, t_stack b);
t_action	*find_best_swap(t_action *lst);

#endif
