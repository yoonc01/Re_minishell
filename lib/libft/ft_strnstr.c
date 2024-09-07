/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:44:31 by ycho2             #+#    #+#             */
/*   Updated: 2023/11/05 16:47:14 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *find, size_t len)
{
	size_t	i;
	size_t	find_i;

	i = 0;
	if (!str && !len)
		return (NULL);
	if (find[i] == 0)
		return ((char *)str);
	while (str[i])
	{
		find_i = 0;
		while (str[i + find_i] == find[find_i] && i + find_i < len)
		{
			find_i++;
			if (find[find_i] == 0)
				return ((char *)(str + i));
		}
		i++;
	}
	return (0);
}
