/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:52:47 by wailas            #+#    #+#             */
/*   Updated: 2025/01/07 09:44:00 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	print_hexa_min(unsigned int nbr)
{
	int	lengt;

	lengt = 0;
	ft_putnbrbase_hexa(nbr, "0123456789abcdef");
	lengt += len_hexa_double(nbr);
	return (lengt);
}

int	print_hexa_max(unsigned int nbr)
{
	int	lengt;

	lengt = 0;
	ft_putnbrbase_hexa(nbr, "0123456789ABCDEF");
	lengt += len_hexa_double(nbr);
	return (lengt);
}

static int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	len_hexa_double(unsigned int nbr)
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

void	ft_putnbrbase_hexa(unsigned int nbr, char const *base)
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
