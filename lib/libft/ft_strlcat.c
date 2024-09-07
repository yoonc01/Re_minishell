/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:29:49 by ycho2             #+#    #+#             */
/*   Updated: 2023/11/05 17:00:41 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	if (!dest && !size)
		return (ft_strlen(src));
	dest_len = ft_strlen((const char *)dest);
	src_len = ft_strlen(src);
	if (dest_len >= size)
		return (src_len + size);
	else
	{
		while (dest_len + i + 1 < size && src[i])
		{
			dest[dest_len + i] = src[i];
			i++;
		}
		dest[dest_len + i] = 0;
		return (src_len + dest_len);
	}
}
