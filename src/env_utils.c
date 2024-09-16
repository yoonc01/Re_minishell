/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngho <youngho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 13:29:28 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/16 16:01:12 by youngho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_env_add(char *env_key)
{
	if (env_key[0] >= '0' && env_key[0] <= '9')
		return (0);
	else
	{
		while (*env_key != 0)
		{
			if (!(ft_isalnum(*env_key)||*env_key=='_'))
				return (0);
			env_key++;
		}
	}
	return (1);
}

int add_new_list(char *env, t_env_list **env_list)
{
	t_env_list	*new_node;
	t_env_list	*tmp_node;
	char		**splited_env;

	new_node = (t_env_list *)malloc(sizeof(t_env_list));
	splited_env = ft_split(env, '=');
	if (check_env_add(splited_env[0]) == 0)
		return (0);
	new_node->env_key = splited_env[0];
	new_node->env_value = splited_env[1];
	new_node->next = NULL;
	if (*env_list == NULL)
		*env_list = new_node;
	else
	{
		tmp_node = *env_list;
		while (tmp_node->next != NULL)
			tmp_node = tmp_node->next;
		tmp_node->next = new_node;
	}
	return (1);
}

// 환경변수 키 값이 적절한지 확인
int		is_valid_env_key(char c)
{
	return (ft_isalnum(c) || c == '_');
}