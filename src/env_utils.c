/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:29:28 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/21 14:26:12 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_env_add(char *env_key)
{
	if (env_key[0] >= '0' && env_key[0] <= '9')
		return (0);
	else
	{
		while (*env_key != 0)
		{
			if (!(ft_isalnum(*env_key) || *env_key=='_'))
				return (0);
			env_key++;
		}
	}
	return (1);
}

// 환경변수 키 값이 적절한지 확인
int		is_valid_env_key(char c)
{
	return (ft_isalnum(c) || c == '_');
}