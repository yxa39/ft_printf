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


int		convert_base_print(long long int num, unsigned int base, char *numerals)
{
	long long int	div;
	long long int	tmp_num;
	int				len;

	div = 1;
	tmp_num = num;
	len = 1;
	while (tmp_num / base > 0)
	{
		tmp_num /= base;
	  	div = div * base;
	  	len++;
	}
	while (div != 1)
	{
		ft_putchar(numerals[num / div]);
		num = num % div;
		div /= base;
	}
	ft_putchar(numerals[num % base]);
	return (len);
}

int		ft_putstr_len(char *str)
{
	ft_putstr(str);
	return ((int)ft_strlen(str));
}

int		print_csp(char *format, va_list *ap)
{
	if (*format == 'c')
	{
		ft_putchar(va_arg(*ap, int));
		return (1);
	}
	if (*format == 's')
		return ft_putstr_len(va_arg(*ap, char *));
	if (*format == 'p')
		return ft_printf("%#lx", (long)va_arg(*ap, void *));
	return (0);
}

int		print_diouxX(char *format, va_list *ap, int len_field)
{
	long long int	num;

	num = va_arg(*ap, long long int);
	if (len_field == 0 && (*format == 'd' || *format == 'i'))
		num = (long long int)(int)num;
	else if (len_field == 0 && ft_strchr("ouxX", *format))
		num = (long long int)(unsigned int)num;
	else if (len_field == 1)
		num = (long long int)(unsigned char)num;
	else if (len_field == 2)
		num = (long long int)(short int)num;
	else if (len_field == 3)
		num = (long long int)(long int)num;
	else if (len_field == 4)
		;
	if (*format == 'd' || *format == 'i')
	{
		ft_putstr(ft_llitoa(num));
		return get_long_strlen(num);
	}
	else if(*format == 'o')
		return (convert_base_print(num, 8, NUMERALS));
	else if (*format == 'u')
		return (convert_base_print(num, 10, NUMERALS));
	else if (*format == 'x')
		return (convert_base_print(num, 16, NUMERALS));
	else if (*format == 'X')
		return (convert_base_print(num, 16, NUMERALS_CAP));
	return (0);
}
int		get_len_field(char **format)
{
	int	type;

	type = 0;
	if (**format == 'h' && *(*format + 1) == 'h')
	{
		type = 1;
		*format = *format + 2;
	}
	else if (**format == 'h' && *(*format + 1) != 'h')
	{
		type = 2;
		*format = *format + 1;
	}
	else if (**format == 'l' && *(*format + 1) != 'l')
	{
		type = 3;
		*format = *format + 1;
	}
	else if (**format == 'l' && *(*format + 1) == 'l')
	{
		type = 4;
		*format = *format + 2;
	}
	else if (**format == 'L')
		(*format)++;
	return (type);
}

int		get_int(double quotient)
{
	double	count;

	count = 0;
	while (count < 9)
	{
		if ((double)(count) == quotient)
		{
			ft_putchar('X');
			return ((int)count);
		}
		else
			count++;
	}
	return ((int)count);
}

void	decimal_print(double num, int precision)
{
	double	tmp;
	int		prec;
	float	dec;

	prec = 1;
	tmp = num;
	while (precision > 0)
	{
		prec *= 10;
		precision--;
	}
	dec = (float)((num - (int)num) * prec);
	ft_printf("%d", (int)dec);
}
int		print_float(va_list *ap, int type)
{
	double	num;
	int		len;

	num = va_arg(*ap, double);
	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	len = ft_printf("%d.", (int)num) + 6;
	decimal_print(num - (double)(int)num, 6);
	type = 0;
	return (len);
}

void	get_flag_field(char **format, int *flag_field)
{
	int i;

	i = 0;
	while (i < 5)
		flag_field[i++] = 0;
	while(ft_strchr("-+ 0#", **format))
	{
		if (**format == '-')
			*flag_field = 1;
		if (**format == '+')
			*(flag_field + 1) = 1;
		if (**format == ' ')
			*(flag_field + 2) = 1;
		if (**format == '0')
			*(flag_field + 3) = 1;
		if (**format == '#')
			*(flag_field + 4) = 1;
		(*format)++;
	}
}

int		get_width(char **format)
{
	int	width;

	width = 0;
	if (ft_strchr("123456789", **format))
	{
		width = **format - '0';
		(*format)++;
	}
	printf("first digit: %d\n", width);
	while (ft_strchr("0123456789", **format))
	{
		width = (**format - '0') + width * 10;
		(*format)++;
	}
	printf("width: %d\n", width);
	return (width);
}

int		what_to_print(char **format, va_list *ap)
{
	int	len_field;
	int	flag_field[5];
	int	width;

	get_flag_field(format, flag_field);
	width = get_width(format);
	len_field = get_len_field(format);
	if (ft_strchr("csp", **format))
		return print_csp(*format, ap);
	else if (ft_strchr("diouxX", **format))
		return print_diouxX(*format, ap, len_field);
	else if (ft_strchr("f", **format))
		return print_float(ap, len_field);
	if (**format == '%')
	{
		ft_putchar(**format++);
		return (1);
	}
	return (0);
}

int	ft_printf(char *format, ...)
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
			len += what_to_print(&format, &ap);
		}
		else
		{
			ft_putchar(*format);
			len++;
		}
		format++;
	}
	va_end(ap);
	return (len);
}
