/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:04:20 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/03 11:14:16 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_child(t_blackhole *blackhole, int pipe_i)
{
	const int	cmd_type = check_cmd_type(
			blackhole->parsed_input[pipe_i].cmd_list->head);

	if (cmd_type <= 6)
	{
		execute_builtin(blackhole, cmd_type, pipe_i);
		exit(blackhole->exit_code);
	}
	else
	{
		exit(
			execute_nbuiltin(blackhole->parsed_input[pipe_i].cmd_list,
				blackhole->env_list));
	}
}

void	ft_handle_last_status(int last_status, t_blackhole *blackhole)
{
	int	status_signal;

	status_signal = last_status & 0x7f;
	if (status_signal == 0)
		blackhole->exit_code = (last_status >> 8) & 0x000000ff;
	else if (status_signal != 0x7f)
	{
		if (status_signal == 3)
			write(2, "Quit: 3\n", 8);
		blackhole->exit_code = (status_signal + 128);
	}
}
