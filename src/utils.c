/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:17:05 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/03 15:13:28 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_strndup(char *s, size_t n)
{
	char	*result;

	result = (char *) malloc(sizeof(char) * (n + 1));
	if (result == 0)
		malloc_fail();
	ft_strlcpy(result, s, n + 1);
	return (result);
}

int	my_strcmp(char *s1, char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
			return (0);
		s1++;
		s2++;
	}
	if (*s1 > *s2)
		return (1);
	else
		return (-1);
}

char	*ft_strnjoin(char *dst, char *attach, size_t att_size)
{
	char	*new_dst;

	new_dst = (char *)malloc(sizeof(char) * (ft_strlen(dst) + att_size + 1));
	if (new_dst == NULL)
		malloc_fail();
	ft_strlcpy(new_dst, dst, ft_strlen(dst) + 1);
	ft_strlcat(new_dst, attach, (ft_strlen(dst) + att_size + 1));
	free(dst);
	return (new_dst);
}

int	ft_isspace(char c)
{
	return ((9 <= c && c <= 13) || c == ' ');
}
