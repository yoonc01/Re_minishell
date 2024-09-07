/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:51:59 by ycho2             #+#    #+#             */
/*   Updated: 2023/11/05 14:36:32 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int val)
{
	int					i;
	int					last;
	unsigned char		temp_val;
	const unsigned char	*temp_str;

	i = 0;
	last = -1;
	temp_str = (const unsigned char *)str;
	temp_val = (unsigned char)val;
	while (temp_str[i])
	{
		if (temp_str[i] == temp_val)
			last = i;
		i++;
	}
	if (temp_val == 0)
		return ((char *)(str + i));
	else if (last == -1)
		return (0);
	else
		return ((char *)(str + last));
}
