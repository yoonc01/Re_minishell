/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:46:49 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/29 21:29:16 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	off_echoctl(void);
static void	on_echoctl(void);

void	set_terminal(int setting)
{
	if (setting)
		on_echoctl();
	else
		off_echoctl();
}

static void	off_echoctl(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

static void	on_echoctl(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}