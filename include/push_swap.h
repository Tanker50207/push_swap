/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:37:00 by gcrepin           #+#    #+#             */
/*   Updated: 2023/11/15 11:56:08 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"

typedef struct s_stack
{
	int	*tab;
	int	size;
	int	size_max;
}				t_stack;

typedef enum e_action
{
	SA,
	SB,
	SS,
	PA,
	PB,
	RA,
	RB,
	RR,
	RRA,
	RRB,
	RRR,
	STOP,
	DEL
}		t_action;

t_stack		*innit_stack(int size);
void		free_stack(t_stack *stack);
t_stack		*push(t_stack *dest_stack, t_stack *src_stack);
t_stack		*swap(t_stack *stack);
t_stack		*rotate(t_stack *stack);
t_stack		*reverse_rotate(t_stack *stack);
t_action	*add_action(t_action *lst, t_action action);
t_action	*sort(t_stack a, t_stack b);
t_action	*optimize(t_action *lst, t_stack a, t_stack b);
void		exec_action(t_action action, t_stack *a, t_stack *b);
int			has_dup(const int *tab, int size);
int			*sanitize_int_tab(int *tab, int size);
void		error(void);
int			free_all_stacks(t_stack *a, t_stack *b, int *tab);
void		error_and_free(t_stack *a, t_stack *b, int *tab);

#endif