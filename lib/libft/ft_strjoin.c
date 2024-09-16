/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngho <youngho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 18:50:18 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/16 16:42:00 by youngho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*concat_str;

	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	concat_str = (char *)malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!concat_str)
		ft_malloc_err();
	concat_str[0] = 0;
	ft_strlcat(concat_str, s1, len_s1 + 1);
	ft_strlcat(concat_str, s2, len_s1 + len_s2 + 1);
	if (!concat_str)
		ft_malloc_err();
	return (concat_str);
}

void	ft_malloc_err(void)
{
	perror("malloc error");
	exit(1);
}
