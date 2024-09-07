/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:46:46 by ycho2             #+#    #+#             */
/*   Updated: 2023/11/04 21:54:16 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t num)
{
	size_t			i;
	unsigned char	*temp_ptr;

	temp_ptr = (unsigned char *)ptr;
	i = 0;
	while (num > i)
		temp_ptr[i++] = (unsigned char)value;
	return (ptr);
}
