/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:05:39 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/29 13:01:39 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_blackhole *blackhole)
{
	int				ret;
	char			*home_value;
	t_inner_block	*current_node;

	current_node = blackhole->parsed_input->cmd_list->head->next;
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
		home_value = get_env("HOME", blackhole->env_list);
		if (home_value == NULL)
			return (EXIT_FAILURE);
		ret = chdir(home_value);
		if (ret < 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
