/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:05:39 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/23 15:12:51 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_inner_block_list *cmd_list)
{
	int				ret;
	char			*home_value;
	t_inner_block	*current_node;

	current_node = cmd_list->head->next;
	if (current_node != NULL)
	{
		ret = chdir(current_node);
		if (ret < 0)
			return (0);//TODO ERROR
	}
	else
	{
		home_value = get_env("HOME");
		if (home_value == NULL)
			return (0);//TODO ERROR
		ret = chdir(home_value);
		if (ret < 0)
			return (0); //TODO ERROR
	}
	return (1);
}
