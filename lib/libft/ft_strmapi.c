/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 11:45:21 by ycho2             #+#    #+#             */
/*   Updated: 2023/10/30 13:08:56 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	s_i;
	char			*new_str;

	new_str = ft_strdup(s);
	if (!new_str)
		return (NULL);
	s_i = 0;
	while (new_str[s_i])
	{
		new_str[s_i] = f(s_i, new_str[s_i]);
		s_i++;
	}
	return (new_str);
}
