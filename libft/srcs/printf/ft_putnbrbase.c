/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:58:14 by wailas            #+#    #+#             */
/*   Updated: 2025/04/24 18:09:22 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	len_hexa(unsigned long long nbr)
{
	int	count;

	count = 0;
	if (nbr == 0)
		return (1);
	while (nbr > 15)
	{
		nbr /= 16;
		count++;
	}
	count++;
	return (count);
}

void	ft_putnbrbase(unsigned long long nbr, char const *base)
{
	int			size_base;
	char		result;

	size_base = len(base);
	result = base[nbr % size_base];
	nbr /= size_base;
	if (nbr != 0)
		ft_putnbrbase(nbr, base);
	ft_putchar(result);
}
