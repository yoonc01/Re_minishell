/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:24:51 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/28 12:26:13 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void redirect_input(t_inner_block *redirect_block, int flag)
{
	int		fd;
	char	*heredoc_str;
	// TODO file open error
	if (flag == REDIR_IN)
	{
		fd = open(redirect_block->str, O_RDONLY, 0);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else // TODO HEREDOC 출력 형식 앞에 > 붙여줘야 함
	{
		fd = open("/var/tmp/tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
		heredoc_str = get_heredoc_input(redirect_block->str);
		write(fd, heredoc_str, ft_strlen(heredoc_str));
		close(fd);
		fd = open("/var/tmp/tmp.txt", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (fd < 0)
	{
		// TODO 파일 오픈 에러 처리
	}
}

void redirect_output(t_inner_block *redirect_block, int flag)
{
	int	fd;

	if (flag == REDIR_OUT)
	{
		fd = open(redirect_block->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else if (flag == REDIR_APPEND)
	{
		fd = open(redirect_block->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}