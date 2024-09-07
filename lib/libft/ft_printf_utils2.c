/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:59:58 by ycho2             #+#    #+#             */
/*   Updated: 2024/04/15 15:01:52 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(unsigned long num);
static int	ft_numlen_hex(unsigned int num);

int	ft_printf_hex(char c, va_list ap)
{
	int				len;
	char			*hex;
	int				i;
	unsigned int	dec_num;
	char			*hex_str;

	dec_num = va_arg(ap, unsigned int);
	len = ft_numlen_hex(dec_num);
	hex_str = (char *)malloc(len);
	if (!hex_str)
		return (-1);
	i = len -1;
	if (c == 'X')
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	while (i >= 0)
	{
		hex_str[i] = hex[dec_num % 16];
		dec_num /= 16;
		i--;
	}
	i = write(1, hex_str, len);
	free(hex_str);
	return (i);
}

char	*ft_uitoa(unsigned int n)
{
	int				len;
	char			*str;
	unsigned long	ul_n;
	int				i;

	i = 0;
	ul_n = (unsigned long)n;
	len = ft_numlen(ul_n);
	str = (char *)ft_calloc(len + 1, 1);
	if (!str)
		return (0);
	if (ul_n == 0)
		str[0] = '0';
	while (ul_n)
	{
		str[--len] = ul_n % 10 + 48;
		ul_n /= 10;
	}
	return (str);
}

static int	ft_numlen(unsigned long num)
{
	int	len;

	len = 0;
	if (num == 0)
		return (1);
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static int	ft_numlen_hex(unsigned int num)
{
	int	len;

	len = 0;
	if (num == 0)
		len++;
	while (num)
	{
		num /= 16;
		len++;
	}
	return (len);
}
