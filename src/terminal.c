/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 22:46:49 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/30 20:32:32 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	echoctl_off(void);
static void	echoctl_on(void);

void	set_terminal(int setting)
{
	if (setting)
		echoctl_on();
	else
		echoctl_off();
}

static void	echoctl_off(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}

static void	echoctl_on(void)
{
	struct termios	t;

	tcgetattr(STDIN_FILENO, &t);
	t.c_lflag |= ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &t);
}
