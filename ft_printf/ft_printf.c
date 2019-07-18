/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 09:13:25 by yxie              #+#    #+#             */
/*   Updated: 2019/07/18 12:37:11 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <libc.h>


void	convert_unsigned_base_print(unsigned int num, unsigned int base, char *numerals)
{
	unsigned int	div;
	unsigned int	tmp_num;

	div = 1;
	tmp_num = num;
	while (tmp_num / base > 0)
	{
		tmp_num /= base;
	  	div = div * base;
	}
	while (div != 1)
	{
		ft_putchar(numerals[num / div]);
		num = num % div;
		div /= base;
	}
	ft_putchar(numerals[num % base]);
}

void	print_csp(char *format, va_list *ap)
{
	if (*format == 'c')
		ft_putchar(va_arg(*ap, int));
	if (*format == 's')
		ft_putstr(va_arg(*ap, char *));
	if (*format == 'p')
		ft_printf("%#l%x", (long)va_arg(*ap, void *));
}

void	print_diouxX(char *format, va_list *ap)
{
	if (*format == 'd' || *format == 'i')
		ft_putstr(ft_itoa(va_arg(*ap, int)));
	if (*format == 'o')
		convert_unsigned_base_print(va_arg(*ap, unsigned int), 8, NUMERALS);
	if (*format == 'u')
		convert_unsigned_base_print(va_arg(*ap, unsigned int), 10, NUMERALS);
	if (*format == 'x')
		convert_unsigned_base_print(va_arg(*ap, unsigned int), 16, NUMERALS);
	if (*format == 'X')
		convert_unsigned_base_print(va_arg(*ap, unsigned int), 16, NUMERALS_CAP);
	
}

void	what_to_print(char *format, va_list *ap)
{
//	void	num;

	if (ft_strchr("csp", *format))
		print_csp(format, ap);

	if (ft_strchr("diouxXhl", *format))
	{
//		if (*format == 'h' && *(format + 1) = 'h')
		if (ft_strchr("diouxX", *format))
			print_diouxX(format, ap);
	}
}

int	ft_printf(const char * restrict format, ...)
{
	va_list	ap;
	int		len;

	len = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			what_to_print((char *)format, &ap);
		}
		else
			ft_putchar(*format);
		format++;
	}
	va_end(ap);
	return (len);
}
