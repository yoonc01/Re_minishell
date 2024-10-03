/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:39:07 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/03 09:42:16 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_parent_after_fork(t_child_util *child_u,
				t_blackhole *blk, int pid);
static void	ft_child_after_fork(t_child_util *child_u,
				t_blackhole *blk);
static void	ft_redirect_fork(t_child_util *child_util, t_blackhole *blackhole);
static void	ft_set_childfd_pipe(t_child_util *child_util);

void	make_child(t_blackhole *blackhole)
{
	int				pid;
	t_child_util	child_util;
	int				status;

	child_util.pipe_i = 0;
	child_util.pipecnt = blackhole->pipe_cnt;
	child_util.prev_pipe = -1;
	child_util.last_child_pid = -1;
	child_util.last_child_status = -1;
	while (child_util.pipe_i <= blackhole->pipe_cnt)
		ft_redirect_fork(&child_util, blackhole);
	set_terminal(1);
	signal(SIGINT, ignore_signal);
	pid = 0;
	while (pid != -1)
	{
		pid = waitpid(-1, &status, 0);
		if (child_util.last_child_pid != -1 && pid == child_util.last_child_pid)
			child_util.last_child_status = status;
	}
	ft_handle_last_status(child_util.last_child_status, blackhole);
}

static void	ft_redirect_fork(t_child_util *child_util, t_blackhole *blackhole)
{
	int	pid;

	ft_set_childfd_pipe(child_util);
	if (set_cur_block_redir(
			blackhole->parsed_input[child_util->pipe_i].redirection_list,
			child_util) == 1)
	{
		if (child_util->pipe_i != 0)
			close(child_util->prev_pipe);
		if (child_util->pipe_i != child_util->pipecnt)
		{
			close(child_util->pipefd[1]);
			child_util->prev_pipe = child_util->pipefd[0];
		}
		child_util->pipe_i++;
		blackhole->exit_code = 1;
		return ;
	}
	signal(SIGQUIT, ignore_signal);
	pid = fork();
	if (pid == 0)
		ft_child_after_fork(child_util, blackhole);
	else
		ft_parent_after_fork(child_util, blackhole, pid);
}

static void	ft_set_childfd_pipe(t_child_util *child_util)
{
	pipe(child_util->pipefd);
	child_util->childfd[0] = STDIN_FILENO;
	child_util->childfd[1] = STDOUT_FILENO;
	if (child_util->pipe_i != 0)
		child_util->childfd[0] = child_util->prev_pipe;
	if (child_util->pipe_i != child_util->pipecnt)
		child_util->childfd[1] = child_util->pipefd[1];
}

static void	ft_parent_after_fork(t_child_util *child_u,
			t_blackhole *blk, int pid)
{
	if (child_u->pipe_i == blk->pipe_cnt)
		child_u->last_child_pid = pid;
	close(child_u->pipefd[1]);
	if (child_u->pipe_i != 0)
		close(child_u->prev_pipe);
	if (child_u->pipe_i != blk->pipe_cnt)
		child_u->prev_pipe = dup(child_u->pipefd[0]);
	close(child_u->pipefd[0]);
	child_u->pipe_i++;
}

static void	ft_child_after_fork(t_child_util *child_u,
			t_blackhole *blk)
{
	close(child_u->pipefd[0]);
	dup2(child_u->childfd[0], STDIN_FILENO);
	dup2(child_u->childfd[1], STDOUT_FILENO);
	close(child_u->pipefd[1]);
	execute_child(blk, child_u->pipe_i);
}
