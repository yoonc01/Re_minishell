/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:47:46 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/30 14:32:15 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_sigint_handle(int signum);

void	signal_default(void)
{
	signal(SIGINT, parent_sigint_handle); //처음에는 개행하고 새로운 라인 그려주면 된다
	signal(SIGQUIT, SIG_IGN); // sigquit이 입력되고 무시하고 계속실행
}

static void	parent_sigint_handle(int signum)
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
