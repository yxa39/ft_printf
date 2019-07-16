/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 09:13:25 by yxie              #+#    #+#             */
/*   Updated: 2019/07/15 12:35:50 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"


char	*get_str(char *format, va_list *ap)
{
	int	a;

	a = va_arg(*ap, int);

	format++;
	return (ft_itoa(a));
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
			ft_putstr(get_str((char *)format, &ap));
		}
		else
			ft_putchar(*format);
		format++;
	}
	return (len);
}
