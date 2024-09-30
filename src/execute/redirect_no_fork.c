/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_no_fork.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 12:24:51 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/30 14:48:54 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_in_no_fork(t_inner_block *redirect_block, int flag)
{
	int		fd;
	char	*heredoc_str;
	int		heredoc_sigint;
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
		heredoc_sigint = ft_heredoc(redirect_block->str, fd);
		if (heredoc_sigint == 1)
			return (1);
		fd = open("/var/tmp/tmp.txt", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (fd < 0)
	{
		// TODO 파일 오픈 에러 처리
	}
	return (0);
}

static void	redir_out_no_fork(t_inner_block *redirect_block, int flag)
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

int	set_redir_no_fork(t_inner_block_list *redirect_list)
{

	int	flag;
	t_inner_block	*curr_redir;
	int				heredoc_sigint;

	flag = 0;
	curr_redir = redirect_list->head;
	while(curr_redir)
	{
		if (curr_redir->type == WORD && flag <= 3)
		{
			heredoc_sigint = redirect_in_no_fork(curr_redir, flag);
			if (heredoc_sigint == 1)
				return (1);
		}
		else
			flag = curr_redir->type;
		curr_redir = curr_redir->next;
	}
	flag = 0;
	curr_redir = redirect_list->head;
	while(curr_redir)
	{
		if (curr_redir->type == WORD && flag >= 4)
			redir_out_no_fork(curr_redir, flag);
		else
			flag = curr_redir->type;
		curr_redir = curr_redir->next;
	}
	return (0);
}
