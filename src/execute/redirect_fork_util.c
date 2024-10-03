/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fork_util.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 09:35:58 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/03 13:28:39 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_output(int *fd_out, char *file_name)
{
	if (*fd_out > 0)
		close(*fd_out);
	*fd_out = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*fd_out < 0)
		return (err_exit(file_name, strerror(errno), 1));
	return (0);
}
