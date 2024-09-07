/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 14:41:27 by ycho2             #+#    #+#             */
/*   Updated: 2024/04/15 15:01:45 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printf_char(va_list ap)
{
	char	out;

	out = (char)va_arg(ap, int);
	return (write(1, &out, 1));
}

int	ft_printf_str(va_list ap)
{
	char	*out;

	out = va_arg(ap, char *);
	if (out == NULL)
		return (write(1, "(null)", 6));
	return (write(1, out, ft_strlen(out)));
}

int	ft_printf_dec(va_list ap)
{
	char	*num;
	int		len;

	num = ft_itoa(va_arg(ap, int));
	if (!num)
		return (-1);
	len = write(1, num, ft_strlen(num));
	free(num);
	return (len);
}

int	ft_printf_u_dec(va_list ap)
{
	char	*num;
	int		len;

	num = ft_uitoa(va_arg(ap, unsigned int));
	if (!num)
		return (-1);
	len = write(1, num, ft_strlen(num));
	free(num);
	return (len);
}
