/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yxie <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 10:21:00 by yxie              #+#    #+#             */
/*   Updated: 2019/07/16 11:50:22 by yxie             ###   ########.fr       */
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
	return (0);
}
