/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 09:13:25 by yxie              #+#    #+#             */
/*   Updated: 2019/07/16 11:58:52 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <libc.h>

void	print_csp(char *format, va_list *ap)
{
	if (*format == 'c')
		ft_putchar(va_arg(*ap, int));
	if (*format == 's')
		ft_putstr(va_arg(*ap, char *));
	if (*format == 'p')
		ft_printf("\n%#lx\n", (long)va_arg(*ap, void *));
}

void	print_diouxX(char *format, va_list *ap)
{
	if (*format == 'd' || *format == 'i')
		ft_putstr(ft_itoa(va_arg(*ap, int)));
	if (*format == 'o')
		ft_printf(ft_itoa(ft_oct(va_arg(*ap, int))))
}

void	what_to_print(char *format, va_list *ap)
{
	if (ft_strchr("csp", *format))
		print_csp(format, ap);
	if (ft_strchr("diouxX", *format))
		print_diouxX(format, ap);
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
