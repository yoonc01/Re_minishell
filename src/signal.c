/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:47:46 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/29 21:27:46 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	control_sigint(int signum);

void	set_signals(void)
{
	signal(SIGINT, control_sigint); //처음에는 개행하고 새로운 라인 그려주면 된다
	signal(SIGQUIT, SIG_IGN); // sigquit이 입력되고 무시하고 계속실행
}

static void	control_sigint(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	ignore_signal(int signum)
{
	if (signum == SIGINT)
		write(STDOUT_FILENO, "\n", 1);
}
