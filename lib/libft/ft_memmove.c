/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:35:34 by ycho2             #+#    #+#             */
/*   Updated: 2023/11/05 15:23:43 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	end_mv(const unsigned char *src, unsigned char *dst, size_t len);
static void	start_mv(const unsigned char *src, unsigned char *dst, size_t len);

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*tmp_src;
	unsigned char		*tmp_dst;

	if (dst == src)
		return (dst);
	tmp_src = (const unsigned char *)src;
	tmp_dst = (unsigned char *)dst;
	if (tmp_src < tmp_dst)
		end_mv(tmp_src, tmp_dst, len);
	else
		start_mv(tmp_src, tmp_dst, len);
	return (dst);
}

static void	end_mv(const unsigned char *src, unsigned char *dst, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
	{
		dst[len - i - 1] = src[len - i - 1];
		i++;
	}
}

static void	start_mv(const unsigned char *src, unsigned char *dst, size_t len)
{
	size_t			i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
}
