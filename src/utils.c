/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 18:17:05 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/15 18:17:56 by hyoyoon          ###   ########.fr       */
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