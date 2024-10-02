/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_fork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 19:10:33 by ycho2             #+#    #+#             */
/*   Updated: 2024/10/02 16:57:19 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redir_input(t_inner_block_list *redir_l, t_child_util *child_util);
static int	redir_output(t_inner_block_list *redir_l, t_child_util *child_util);
static void	set_pipe(t_child_util *child_util);

int	set_child_redir(t_inner_block_list *redirect_list, t_child_util *child_util)
{
	int	err_flag;

	set_pipe(child_util);
	err_flag = redir_input(redirect_list, child_util);
	if (err_flag)
		return (1);
	err_flag = redir_output(redirect_list, child_util);
	if (err_flag)
		return (1);
	return (0);
}

static int	redir_input(t_inner_block_list *redirect_list,
				t_child_util *child_util)
{
	int				fd;
	int				flag;
	t_inner_block	*cur_redir;
	int				heredoc_sigint;

	fd = -1;
	flag = 0;
	cur_redir = redirect_list->head;
	while (cur_redir)
	{
		if (cur_redir->type == WORD)
		{
			if (flag == REDIR_IN)
			{
				if (fd > 0)
					close(fd);
				fd = open(cur_redir->str, O_RDONLY, 0);
				if (fd < 0)
				{
					err_exit(cur_redir->str, strerror(errno));
					return (1);
				}
			}
			else if (flag == HEREDOC)
			{
				if (fd > 0)
					close(fd);
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
		child_util->childfd[0] = fd;
	return (0);
}

static int	redir_output(t_inner_block_list *redirect_list,
				t_child_util *child_util)
{
	int				fd;
	int				flag;
	t_inner_block	*cur_redir;

	flag = 0;
	fd = -1;
	cur_redir = redirect_list->head;
	while (cur_redir)
	{
		if (cur_redir->type == WORD)
		{
			if (flag == REDIR_OUT)
			{
				if (fd > 0)
					close(fd);
				fd = open(cur_redir->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd < 0)
				{
					err_exit(cur_redir->str, strerror(errno));
					return (1);
				}
			}
			else if (flag == REDIR_APPEND)
			{
				if (fd > 0)
					close(fd);
				fd = open(cur_redir->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd < 0)
				{
					err_exit(cur_redir->str, strerror(errno));
					return (1);
				}
			}
		}
		else
			flag = cur_redir->type;
		cur_redir = cur_redir->next;
	}
	if (fd >= 0)
		child_util->childfd[1] = fd;
	return (0);
}

static void	set_pipe(t_child_util *child_util)
{
	if (child_util->pipe_i != 0) // 첫번째 커맨드가 아니면 prev_pipe 를 std_in으로
		child_util->childfd[0] = child_util->prev_pipe;
	if (child_util->pipe_i != child_util->pipecnt) // 마지막 커맨드가 아니면 pipefd[1]을 stdout 으로
		child_util->childfd[1] = child_util->pipefd[1];
}
