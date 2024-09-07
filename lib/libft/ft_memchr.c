/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:00:26 by ycho2             #+#    #+#             */
/*   Updated: 2023/11/05 14:36:59 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int val, size_t num)
{
	size_t				i;
	unsigned char		temp_val;
	const unsigned char	*temp_ptr;

	i = 0;
	temp_ptr = (const unsigned char *)ptr;
	temp_val = (unsigned char)val;
	while (i < num)
	{
		if (temp_ptr[i] == temp_val)
			return ((void *)(ptr + i));
		i++;
	}
	return (0);
}
