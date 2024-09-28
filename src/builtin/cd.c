/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:05:39 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/28 16:22:14 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_inner_block_list *cmd_list, t_env_list *env_list)
{
	int				ret;
	char			*home_value;
	t_inner_block	*current_node;

	current_node = cmd_list->head->next;
	if (current_node != NULL)
	{
		ret = chdir(current_node->str);
		if (ret < 0)
		{
			builtin_error("cd: no such file or directory: ", current_node->str);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		home_value = get_env("HOME", env_list);
		if (home_value == NULL)
			return (EXIT_FAILURE);
		ret = chdir(home_value);
		if (ret < 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
