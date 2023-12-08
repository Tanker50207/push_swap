/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:33:45 by gcrepin           #+#    #+#             */
/*   Updated: 2023/12/07 15:33:55 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	error(void)
{
	ft_printf("Error\n");
	exit(EXIT_FAILURE);
}

void	error_and_free(t_stack *a, t_stack *b, int *tab)
{
	free_all_stacks(a, b);
	if (tab)
		free(tab);
	error();
}

int	is_valid_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (ft_strlen(str) > (size_t)(11 - (ft_isdigit(str[0]))))
		return (0);
//	if (ft_atoi(str) > 2147483647 || ft_atoi(str) < -2147483648)
//		return (0);
	return (1);
}//TODO: finish