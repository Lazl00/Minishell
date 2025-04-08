/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_untils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 14:04:17 by wailas            #+#    #+#             */
/*   Updated: 2025/01/07 09:44:30 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	print_str(const char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (count += write(1, "(null)", 6));
	while (*str)
	{
		write(1, str, 1);
		count++;
		str++;
	}
	return (count);
}

long int	get_longueur(long int nbr)
{
	int	longueur;

	longueur = 0;
	if (nbr < 0)
	{
		longueur++;
		nbr = -nbr;
	}
	while (nbr >= 10)
	{
		longueur++;
		nbr /= 10;
	}
	longueur++;
	return (longueur);
}

int	print_int(int nbr)
{
	int			count;
	char		c;
	long int	nombre;

	nombre = nbr;
	count = get_longueur(nombre);
	if (nombre < 0)
	{
		write(1, "-", 1);
		nombre = -nombre;
	}
	if (nombre >= 10)
		print_int(nombre / 10);
	c = (nombre % 10) + '0';
	write(1, &c, 1);
	return (count);
}
