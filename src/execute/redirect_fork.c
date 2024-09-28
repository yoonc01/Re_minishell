/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:10:33 by ycho2             #+#    #+#             */
/*   Updated: 2024/09/28 21:58:13 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redir_input(t_inner_block_list *redir_l, t_pipe_util *pipe_util);
static void	redir_output(t_inner_block_list *redir_l, t_pipe_util *pipe_util);
static void	set_pipe(t_pipe_util *pipe_util);

void	set_child_redir(t_inner_block_list *redirect_list, t_pipe_util *pipe_util)
{
	set_pipe(pipe_util);
	redir_input(redirect_list, pipe_util);
	redir_output(redirect_list, pipe_util);
}

static void	redir_input(t_inner_block_list *redirect_list, t_pipe_util *pipe_util)
{
	int				fd;
	char			*heredoc_str;
	int				flag;
	t_inner_block	*cur_redir;

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
				fd = open("/var/tmp/tmp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
				heredoc_str = get_heredoc_input(cur_redir->str);
				write(fd, heredoc_str, ft_strlen(heredoc_str));
				free(heredoc_str);
				fd = open("/var/tmp/tmp.txt", O_RDONLY);
				// TODO heredoc tmp.txt를 unlink해줘야 함
			}
		}
		else
			flag = cur_redir->type;
		cur_redir = cur_redir->next;
	}
	pipe_util->childfd[0] = fd;
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
	pipe_util->childfd[1] = fd;
}

static void	set_pipe(t_pipe_util *pipe_util)
{
	int	*child_fd;

	if (pipe_util->pipe_i != 0) // 첫번째 커맨드가 아니면 prev_pipe 를 std_in으로
		pipe_util->childfd[0] = pipe_util->prev_pipe;
	if (pipe_util->pipe_i != pipe_util->pipecnt) // 마지막 커맨드가 아니면 pipefd[1]을 stdout 으로
		pipe_util->childfd[1] = pipe_util->pipefd[1];
}
