/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:04:20 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/02 18:39:10 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child(t_blackhole *blackhole, int pipe_i)
{
	const int	cmd_type = check_cmd_type(
			blackhole->parsed_input[pipe_i].cmd_list->head);

	if (cmd_type <= 6)
	{
		execute_builtin(blackhole, cmd_type);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execute_nbuiltin(
			blackhole->parsed_input[pipe_i].cmd_list, blackhole->env_list);
		exit(EXIT_SUCCESS);
	}
}
