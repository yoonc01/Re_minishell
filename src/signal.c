/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:47:46 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/18 18:33:00 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signals(int signal);

void	set_signals(void)
{
	struct sigaction sa;

	sa.sa_flags = 0;
	sa.sa_handler = handle_signals;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
}

static void	handle_signals(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		printf("\n");
		rl_on_new_line();
		rl_redisplay();
	}
	// if (signal == SIGTERM)
	// {
	// 	rl_replace_line("exit", 0);
	// 	printf("\n");
	// 	rl_on_new_line();
	// 	rl_redisplay();
	// 	exit(0);
	// }
}
