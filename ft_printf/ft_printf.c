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

void	print_spaces(int width, int len, int *flag_field, int precision)
{
	if (width > len && *flag_field == 0 && (*(flag_field + 3) == 0 || *(flag_field + 5) == 1) && *(flag_field + 5) == 0)
	{
		while (width-- > len)
			ft_putchar(' ');
	}
	if (*flag_field == 0 && *(flag_field + 5) == 1 && width > (len > precision ? precision : len) && (*(flag_field + 3) == 0 || *(flag_field + 5) == 1))
	{
		while (width-- > (len > precision ? precision : len))
			ft_putchar(' ');
	}
}


int		print_zeros(int width, int len, int *flag_field, int precision, int hash_len)
{
	int	tmp;

	if (width > len && *(flag_field + 3) == 1 && *flag_field == 0 && *(flag_field + 5) == 0)
	{
		tmp = width;
		while (width-- > len)
			ft_putchar('0');
		len = tmp;
	}
//	printf("len: %d\n", len);
//	printf("width: %d\n", width);
//	printf("precision: %d\n", precision);
	if (precision > (len - hash_len)  && *(flag_field + 5) == 1)
	{
		tmp = precision;
		while (precision > (len - hash_len))
		{
			ft_putchar('0');
			precision--;
		}
		len = tmp;
	}
	return (len);
}

void	print_hash(int *flag_field, int base, long long int num, int precision)
{
	if (num != 0)
	{
		if (*(flag_field + 4) == 1)
		{
			if (base == 8)
				ft_putchar('0');
			if (base == 16)
				ft_putstr("0x");
			if (base == 17)
				ft_putstr("0X");
		}
	}
	else if (num == 0 && *(flag_field + 5) == 1 && precision == 0)
		if (*(flag_field + 4) == 1 && base == 8)
			ft_putchar('0');
}

int		print_plus(int *flag_field, long long int num)
{
	int	len;

	len = 0;
	if (num >= 0)
	{
		if (*(flag_field + 1) == 1)
		{
			ft_putchar('+');
			len = 1;
		}
		else if (*(flag_field + 2) == 1)
		{
			ft_putchar(' ');
			len = 1;
		}
	}
	return (len);
}

int		hash_len(int *flag_field, int base, long long int num, int precision)
{
	if (num != 0)
	{
		if (*(flag_field + 4) == 1)
		{
			if (base == 8)
				return (1);
			if (base == 16)
				return (2);
			if (base == 17)
				return (2);
		}
	}
	else if (num == 0 && *(flag_field + 5) == 1 && precision == 0)
		if (*(flag_field + 4) == 1 && base == 8)
			return (1);
	return (0);
}

int		convert_base_print(unsigned long long int num, unsigned int base, char *numerals, int width, int *flag_field, int precision)
{
	unsigned long long int	div;
	unsigned long long int	tmp_num;
	int				len;
	unsigned int				base_tmp;

	div = 1;
	tmp_num = num;
	base_tmp = base;
	len = 1;
	if (base == 17)
		base = 16;
	while ((unsigned long long)(tmp_num / base) > 0)
	{
		tmp_num /= base;
	  	div = div * base;
	  	len++;
	}
//	printf("len: %d\n", len);
	if (num == 0 && precision == 0 && *(flag_field + 5) == 1)
		len = 0;
	len += hash_len(flag_field, base_tmp, num, precision);
	print_spaces(width, (len > precision ? len: precision), flag_field, (precision < len ? len : precision));
	print_hash(flag_field, base_tmp, num, precision);
	if (num == 0 && precision == 0 && *(flag_field + 5) == 1)
		return (len);
	len = print_zeros(width, len, flag_field, precision, hash_len(flag_field, base_tmp, num, precision));
	while (div != 1)
	{
		ft_putchar(numerals[num / div]);
		num = num % div;
		div /= base;
	}
	ft_putchar(numerals[num % base]);
	return (len);
}

int		ft_putstr_len(char *str, int width, int *flag_field, int precision)
{
	int	len;

	if (str == NULL)
		len = ft_strlen("(null)");
	else
		len = (int)ft_strlen(str);
//	printf("%d\n", width);
//	printf("%d\n", len);
//	printf("%d\n", precision);
	print_spaces(width, len, flag_field, precision);
	if (str == NULL)
		ft_putstr("(null)");
	else if (precision < len && *(flag_field + 5) == 1)
	{
		len = precision;
		while (precision-- > 0)
			ft_putchar(*(str++));
	}
	else
		ft_putstr(str);
	return (len);
}

int		print_csp(char *format, va_list *ap, int width, int *flag_field, int precision)
{
	int	len;
	if (*format == 'c')
	{
		len = 1;
		print_spaces(width, len, flag_field, precision);
		precision = 0;
		len = print_zeros(width, len, flag_field, precision, 0);
		ft_putchar(va_arg(*ap, int));
		return (len);
	}
	if (*format == 's')
		return ft_putstr_len(va_arg(*ap, char *), width, flag_field, precision);
	if (*format == 'p')
		return ft_printf("%#lx", (long)va_arg(*ap, void *));
	return (0);
}

int		print_di(long long int num, int width, int *flag_field, int precision)
{
	int	len;

	len = get_long_strlen(num);
	if (num + 1 == -9223372036854775807)
		ft_putchar('-');
	if (num - 1 == 9223372036854775807 || num + 1 == -9223372036854775807)
	{
		ft_putstr("9223372036854775808");
		return (len);
	}
//	printf("len: %d\n", len);
	len += print_plus(flag_field, num);
	if (num == 0 && precision == 0 && *(flag_field + 5) == 1)
		len = 0;
	print_spaces(width, (len > precision ? len: precision), flag_field, precision);
	if (num == 0 && precision == 0 && *(flag_field + 5) == 1)
		return (0);
	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	len = print_zeros(width, len, flag_field, precision, 0);
	ft_putstr(ft_llitoa(num));
	return (len);
}

int		print_diouxX(char *format, va_list *ap, int len_field, int width, int *flag_field, int precision)
{
	long long int	num;

	num = va_arg(*ap, long long int);
	if (*format == 'd' || *format == 'i')
	{
		if (len_field == 0)
			num = (int)num;
		else if (len_field == 1)
			num = (char)num;
		else if (len_field == 2)
			num = (short int)num;
		else if (len_field == 3)
			num = (long int)num;
		return (print_di(num, width, flag_field, precision));
	}
	if (ft_strchr("ouxX", *format))
	{
		if (len_field == 0)
			num = (unsigned int)num;
		else if (len_field == 1)
			num = (unsigned char)num;
		else if (len_field == 2)
			num = (unsigned short int)num;
		else if (len_field == 3)
			num = (unsigned long int)num;
		if(*format == 'o')
			return (convert_base_print(num, 8, NUMERALS, width, flag_field, precision));
		else if (*format == 'u')
			return (convert_base_print(num, 10, NUMERALS, width, flag_field, precision));
		else if (*format == 'x')
			return (convert_base_print(num, 16, NUMERALS, width, flag_field, precision));
		else if (*format == 'X')
			return (convert_base_print(num, 17, NUMERALS_CAP, width, flag_field, precision));
	}
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
		dec = (float)((num - (int)num) * prec);
		ft_printf("%d", (int)dec);
	}
}
int		print_float(va_list *ap, int type, int width, int *flag_field, int precision)
{
	double	num;
	int		len;

	num = va_arg(*ap, double);
	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	len = get_long_strlen(num) + 7;
	print_spaces(width, len, flag_field, precision);
	ft_printf("%d.", (int)num);
	decimal_print(num - (double)(int)num, 6);
	type = 0;
	return (len > width ? len : width);
}

void	get_flag_field(char **format, int *flag_field)
{
	int i;

	i = 0;
	while (i < 6)
		*(flag_field + i++) = 0;
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
	//printf("first digit: %d\n", width);
	while (ft_strchr("0123456789", **format))
	{
		width = (**format - '0') + width * 10;
		(*format)++;
	}
//	printf("width: %d\n", width);
	return (width);
}

int		print_left_spaces(int width, int len, int *flag_field)
{
	int	tmp;

	if (width > len && *flag_field == 1)
	{
		tmp = width;
		while (width-- > len)
			ft_putchar(' ');
		len = tmp;
	}
	return (len);

}

void	get_precision_field(char **format, int *flag_field)
{
	if (**format == '.')
	{
		*(flag_field + 5) = 1;
		(*format)++;
	}
}

int		what_to_print(char **format, va_list *ap)
{
	int	len_field;
	int	flag_field[5];
	int	width;
	int precision;
	int	len;

	len = 0;
	get_flag_field(format, flag_field);
	width = get_width(format);
	get_precision_field(format, flag_field);
	precision = get_width(format);
	len_field = get_len_field(format);
	if (ft_strchr("csp", **format))
		len = print_csp(*format, ap, width, flag_field, precision);
	else if (ft_strchr("diouxX", **format))
		len = print_diouxX(*format, ap, len_field, width, flag_field, precision);
	else if (ft_strchr("f", **format))
		len = print_float(ap, len_field, width, flag_field, precision);
	if (**format == '%')
	{
		len = 1;
		print_spaces(width, len, flag_field, precision);
		ft_putchar(**format++);
	}
	print_left_spaces(width, len, flag_field);
	return (len > width ? len : width);
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
