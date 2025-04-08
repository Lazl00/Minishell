/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:44:35 by wailas            #+#    #+#             */
/*   Updated: 2025/01/07 09:44:24 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	print_unsigned(unsigned int nbr)
{
	int			count;
	char		c;
	long int	nombre;

	nombre = nbr;
	count = get_longueur(nombre);
	if (nombre >= 10)
		print_int(nombre / 10);
	c = (nombre % 10) + '0';
	write(1, &c, 1);
	return (count);
}
