/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:47:46 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/02 17:58:21 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parent_sigint_handle(int signum);

void	signal_default(void)
{
	signal(SIGINT, parent_sigint_handle);
	signal(SIGQUIT, SIG_IGN);
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
