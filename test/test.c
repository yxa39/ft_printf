/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 10:21:00 by yxie              #+#    #+#             */
/*   Updated: 2019/07/18 13:01:22 by yxie             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "test.h"

int	main()
{
	printf("ft_printf:\n");
	ft_printf("aa%saa%s\n", "bb", "cc");
	printf("aa%saa%s\n\n", "bb", "cc");
	ft_printf("abc%c\n", 'c');
	printf("abc%c\n\n", 'c');
	ft_printf("abc%p\n", "abc");
	printf("abc%p\n\n", "abc");
	ft_printf("abc%d\n", 1);
	printf("abc%d\n\n", 1);
	ft_printf("abc%o\n", -111111111111);
	printf("abc%o\n\n", -111111111111);
	ft_printf("abc%u\n", -111111);
	printf("abc%u\n\n", -111111);
	ft_printf("abc%x\n", -111111);
	printf("abc%x\n\n", -111111);
	ft_printf("abc%X\n", -111111);
	printf("abc%X\n\n", -111111);
	//ft_printf("abc%hhX\n", -111111);
	printf("abc%hho\n\n", (unsigned char)19);
	return (0);
}
