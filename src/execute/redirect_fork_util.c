/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fork_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:40:02 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/02 19:18:16 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_out_fork_word(int *flag, t_inner_block *cur_redir, int *fd)
{
	if (*flag == REDIR_OUT)
	{
		if (*fd > 0)
			close(*fd);
		*fd = open(cur_redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (*fd < 0)
		{
			err_exit(cur_redir->str, strerror(errno));
			return (1);
		}
	}
	else if (*flag == REDIR_APPEND)
	{
		if (*fd > 0)
			close(*fd);
		*fd = open(cur_redir->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (*fd < 0)
		{
			err_exit(cur_redir->str, strerror(errno));
			return (1);
		}
	}
	return (0);
}
