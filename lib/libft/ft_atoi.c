/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 15:43:18 by ycho2             #+#    #+#             */
/*   Updated: 2024/04/29 18:22:38 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void	check_int_range(long long num);

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	num;

	num = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-' || str [i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str [i] <= '9')
			num = num * 10 + (str[i] - '0');
		i++;
	}
	check_int_range(num);
	return ((int)(sign * num));
}

static void	check_int_range(long long num)
{
	if (num > 2147483647 || num < -2147483648)
	{
		ft_printf("Error2\n");
		exit(1);
	}
}

int	ft_atoi16(const char *str)
{
	int			i;
	long long	num;

	num = 0;
	i = 2;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			num = num * 16 + (str[i] - '0');
		else if (str[i] >= 'A' && str[i] <= 'F')
			num = num * 16 + (str[i] - 'A' + 10);
		else if (str[i] >= 'a' && str[i] <= 'f')
			num = num * 16 + (str[i] - 'a' + 10);
		i++;
	}
	return ((int)num);
}
