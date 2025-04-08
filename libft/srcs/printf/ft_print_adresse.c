/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_adresse.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:33:51 by wailas            #+#    #+#             */
/*   Updated: 2025/01/07 09:44:44 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	print_adresse(unsigned long long *adresse)
{
	int	lengt;

	lengt = 0;
	if (adresse == NULL)
		return (lengt += write(1, "(nil)", 5));
	lengt += write(1, "0x", 2);
	ft_putnbrbase((unsigned long long)adresse, "0123456789abcdef");
	lengt += len_hexa((unsigned long long)adresse);
	return (lengt);
}
