/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 11:58:14 by wailas            #+#    #+#             */
/*   Updated: 2025/01/07 09:44:36 by wailas           ###   ########.fr       */
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

	size_base = ft_strlen(base);
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr = -nbr;
	}
	result = base[nbr % size_base];
	nbr /= size_base;
	if (nbr != 0)
		ft_putnbrbase(nbr, base);
	ft_putchar(result);
}
