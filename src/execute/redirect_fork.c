/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:10:33 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/30 12:36:25 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_input(t_inner_block_list *redir_l, t_pipe_util *pipe_util);
static void	redir_output(t_inner_block_list *redir_l, t_pipe_util *pipe_util);
static void	set_pipe(t_pipe_util *pipe_util);

int	set_child_redir(t_inner_block_list *redirect_list, t_pipe_util *pipe_util)
{
	int	heredoc_sigint;

	set_pipe(pipe_util);
	heredoc_sigint = redir_input(redirect_list, pipe_util);
	if (heredoc_sigint)
		return (1);
	redir_output(redirect_list, pipe_util);
	return (0);
}

static int	redir_input(t_inner_block_list *redirect_list, t_pipe_util *pipe_util)
{
	int				fd;
	int				flag;
	t_inner_block	*cur_redir;
	int				heredoc_sigint;

	fd = -1;
	flag = 0;
	cur_redir = redirect_list->head;
	// TODO file open error
	while(cur_redir)
	{
		if (cur_redir->type == WORD)
		{
			if (flag == REDIR_IN)
			{
				if (fd > 0)
					close(fd);
				fd = open(cur_redir->str, O_RDONLY, 0);
			}
			else if (flag == HEREDOC)// TODO HEREDOC 출력 형식 앞에 > 붙여줘야 함
			{
				if (fd > 0)
					close(fd);
				// ft_heredoc(&fd, cur_redir->str);
				fd = open("/var/tmp/tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
				heredoc_sigint = ft_heredoc(cur_redir->str, fd);
				if (heredoc_sigint == 1)
					return (1);
				fd = open("/var/tmp/tmp.txt", O_RDONLY);
				// TODO heredoc tmp.txt를 unlink해줘야 함
			}
		}
		else
			flag = cur_redir->type;
		cur_redir = cur_redir->next;
	}
	if (fd >= 0)
		pipe_util->childfd[0] = fd;
	return (0);
}



static void	redir_output(t_inner_block_list *redirect_list, t_pipe_util *pipe_util)
{
	int				fd;
	int				flag;
	t_inner_block	*cur_redir;

	flag = 0;
	fd = -1;
	cur_redir = redirect_list->head;
	while(cur_redir)
	{
		if (cur_redir->type == WORD)
		{
			if (flag == REDIR_OUT)
			{
				if (fd > 0)
					close(fd);
				fd = open(cur_redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			}
			else if (flag == REDIR_APPEND)
			{
				if (fd > 0)
					close(fd);
				fd = open(cur_redir->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
			}
		}
		else
			flag = cur_redir->type;
		cur_redir = cur_redir->next;
	}
	if (fd >= 0)
		pipe_util->childfd[1] = fd;
}

static void	set_pipe(t_pipe_util *pipe_util)
{
	if (pipe_util->pipe_i != 0) // 첫번째 커맨드가 아니면 prev_pipe 를 std_in으로
		pipe_util->childfd[0] = pipe_util->prev_pipe;
	if (pipe_util->pipe_i != pipe_util->pipecnt) // 마지막 커맨드가 아니면 pipefd[1]을 stdout 으로
		pipe_util->childfd[1] = pipe_util->pipefd[1];
}
