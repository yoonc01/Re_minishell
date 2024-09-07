/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 20:38:26 by ycho2             #+#    #+#             */
/*   Updated: 2024/04/15 15:01:58 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_addr_len(unsigned long addr);

int	ft_printf_addr(va_list ap)
{
	int				len;
	const char		*hex = "0123456789abcdef";
	unsigned long	addr;
	int				i;
	char			*addr_16;

	addr = (unsigned long)va_arg(ap, void *);
	len = ft_addr_len(addr);
	addr_16 = (char *)malloc(len);
	if (!addr_16)
		return (-1);
	addr_16[0] = '0';
	addr_16[1] = 'x';
	i = len - 1;
	while (i >= 2)
	{
		addr_16[i] = hex[addr % 16];
		addr /= 16;
		i--;
	}
	i = write(1, addr_16, len);
	free(addr_16);
	return (i);
}

static int	ft_addr_len(unsigned long addr)
{
	int	len;

	len = 2;
	if (addr == 0)
		len++;
	while (addr)
	{
		addr /= 16;
		len++;
	}
	return (len);
}
