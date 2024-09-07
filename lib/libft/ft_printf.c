/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 16:47:10 by ycho2             #+#    #+#             */
/*   Updated: 2024/04/15 15:03:47 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf(const char *string, ...)
{
	va_list	ap;
	int		len;
	int		i;
	int		attach;

	len = 0;
	i = 0;
	va_start(ap, string);
	while (string[i])
	{
		if (string[i] != '%')
			attach = write(1, &string[i], 1);
		else
			attach = ft_conversion(string[++i], ap);
		if (attach == -1)
			return (-1);
		len += attach;
		i++;
	}
	va_end(ap);
	return (len);
}

int	ft_conversion(char c, va_list ap)
{
	int	attach;

	attach = 0;
	if (c == '%')
		attach = write(1, &c, 1);
	else if (c == 'c')
		attach = ft_printf_char(ap);
	else if (c == 's')
		attach = ft_printf_str(ap);
	else if (c == 'p')
		attach = ft_printf_addr(ap);
	else if (c == 'd' || c == 'i')
		attach = ft_printf_dec(ap);
	else if (c == 'u')
		attach = ft_printf_u_dec(ap);
	else if (c == 'X' || c == 'x')
		attach = ft_printf_hex(c, ap);
	return (attach);
}
