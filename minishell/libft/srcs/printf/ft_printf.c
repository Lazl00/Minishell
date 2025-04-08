/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wailas <wailas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:25:54 by wailas            #+#    #+#             */
/*   Updated: 2025/01/07 09:44:33 by wailas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	print_caractere(char c)
{
	return (write(1, &c, 1));
}

int	printf_type(const char str, va_list args)
{
	int		count;

	count = 0;
	if (str == 'd' || str == 'i')
		count += print_int(va_arg(args, int));
	else if (str == 'c')
		count += print_caractere(va_arg(args, int));
	else if (str == 's')
		count += print_str(va_arg(args, char *));
	else if (str == 'p')
		count += print_adresse(va_arg(args, void *));
	else if (str == 'u')
		count += print_unsigned(va_arg(args, unsigned int));
	else if (str == 'x')
		count += print_hexa_min(va_arg(args, int));
	else if (str == 'X')
		count += print_hexa_max(va_arg(args, int));
	else if (str == '%')
		count += print_caractere('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		count;

	count = 0;
	i = 0;
	if (!format)
		return (-1);
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			count += printf_type(format[i + 1], args);
			i++;
		}
		else
			count += print_caractere(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
