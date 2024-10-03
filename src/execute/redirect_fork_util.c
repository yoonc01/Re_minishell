/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fork_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 09:35:58 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/03 09:44:17 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_output(int *fd_out, char *file_name)
{
	if (*fd_out > 0)
		close(*fd_out);
	*fd_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out < 0)
	{
		err_exit(file_name, strerror(errno));
		return (1);
	}
	return (0);
}
