/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 01:21:34 by ycho2             #+#    #+#             */
/*   Updated: 2023/11/05 14:12:00 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_find_start(char const *s1, char const *set);
static size_t	ft_find_end(char const *s1, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;

	start = ft_find_start(s1, set);
	end = ft_find_end(s1, set);
	if (start > end)
		return ((char *)ft_calloc(1, 1));
	else
		return (ft_substr(s1, start, end - start + 1));
}

static size_t	ft_find_start(char const *s1, char const *set)
{
	size_t	start;
	size_t	set_i;

	start = 0;
	while (s1[start])
	{
		set_i = 0;
		while (set[set_i])
		{
			if (s1[start] == set[set_i])
				break ;
			set_i++;
		}
		if (set[set_i] == 0)
			break ;
		start++;
	}
	return (start);
}

static size_t	ft_find_end(char const *s1, char const *set)
{
	size_t	end;
	size_t	set_i;

	end = ft_strlen(s1) - 1;
	while (end >= 0)
	{
		set_i = 0;
		while (set[set_i])
		{
			if (s1[end] == set[set_i])
				break ;
			set_i++;
		}
		if (set[set_i] == 0)
			break ;
		end--;
	}
	return (end);
}
