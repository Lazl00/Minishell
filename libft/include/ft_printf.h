/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcournoy <lcournoy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 17:41:00 by wailas            #+#    #+#             */
/*   Updated: 2025/04/24 18:09:46 by lcournoy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>

/*	printf	functions	*/
int			print_charactere(char c);
int			printf_type(const char str, va_list args);
int			print_str(const char *str);
int			print_int(int nbr);
int			ft_printf(const char *str, ...);
int			print_adresse(unsigned long long *adresse);
size_t		len(const char *str);
void		ft_putnbrbase(unsigned long long nbr, char const *base);
int			len_hexa(unsigned long long nbr);
int			print_unsigned(unsigned int nbr);
long int	get_longueur(long int nbr);
int			print_hexa_min(unsigned int nbr);
int			print_hexa_max(unsigned int nbr);
int			len_hexa_double(unsigned int nbr);
void		ft_putnbrbase_hexa(unsigned int nbr, char const *base);

#endif