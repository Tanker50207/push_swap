/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_verifyer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcrepin <gcrepin@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:55:20 by gcrepin           #+#    #+#             */
/*   Updated: 2023/12/07 12:24:16 by gcrepin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	has_dup(const int	*tab, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (tab[i] == tab[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	*dup_int_tab(const int	*tab, int size)
{
	int	i;
	int	*new_tab;

	new_tab = (int *)malloc(sizeof(int) * size);
	if (!new_tab)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_tab[i] = tab[i];
		i++;
	}
	return (new_tab);
}

static int	find_index(const int	*tab, int size, int nb)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i] == nb)
			return (i);
		i++;
	}
	return (-1);
}

int	*sanitize_int_tab(int	*tab, int size)
{
	int	i;
	int	*ref_tab;

	ref_tab = dup_int_tab(tab, size);
	if (!ref_tab)
	{
		free(tab);
		return (NULL);
	}
	ft_sort_int_tab(ref_tab, size);
	i = 0;
	while (i < size)
	{
		tab[i] = find_index(ref_tab, size, tab[i]);
		i++;
	}
	free(ref_tab);
	return (tab);
}
