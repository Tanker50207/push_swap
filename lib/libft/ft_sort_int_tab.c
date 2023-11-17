/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 12:02:26 by gcrepin           #+#    #+#             */
/*   Updated: 2023/09/17 13:28:00 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_sort_int_tab(int *tab, int size)
{
	int	pos;
	int	l_val;
	int	t_val;

	pos = 1;
	while (pos < size)
	{
		if (tab[pos] < tab[pos - 1])
		{
			l_val = tab[pos - 1];
			t_val = tab[pos];
			tab[pos] = l_val;
			tab[pos - 1] = t_val;
			if (pos == 1)
				pos++;
			else
				pos--;
		}
		else
			pos++;
	}
}
