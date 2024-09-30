/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:39:07 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/30 18:33:56 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child(t_blackhole *blackhole, int pipe_i);
static void	ft_handle_last_status(int last_status, t_blackhole *blackhole);

void make_child(t_blackhole *blackhole)
{
	int				pid;
	t_child_util	child_util;
	int				heredoc_sigint;
	int				status;

	child_util.pipe_i = 0;
	child_util.pipecnt = blackhole->pipe_cnt;
	child_util.prev_pipe = -1;
	child_util.last_child_pid = -1;
	child_util.last_child_status = -1;
	// export 구조체에 환경변수
	while (child_util.pipe_i <= blackhole->pipe_cnt)
	{
		pipe(child_util.pipefd);
		child_util.childfd[0] = STDIN_FILENO;
		child_util.childfd[1] = STDOUT_FILENO;
		heredoc_sigint = set_child_redir(blackhole->parsed_input[child_util.pipe_i].redirection_list, &child_util);
		if (heredoc_sigint == 1)
		{
			blackhole->exit_code = 1;
			break ;
		}
		signal(SIGQUIT, ignore_signal); // 자식에서execve실행하면 시그널 핸들러 초기화된다
		pid = fork();
		if (pid < 0)
			exit(1); // TODO
		else if (pid == 0) //자식
		{
			close(child_util.pipefd[0]); // 부모가 pipefd 들고 있으므로 close해도 된다
			dup2(child_util.childfd[0], STDIN_FILENO);
			dup2(child_util.childfd[1], STDOUT_FILENO);
			close(child_util.pipefd[1]); // 리다이렉션 끝났으니까 닫아도 된다
			// 아직 이전 자식의 출력이 끝나지 않았을 수 있으므로 prev_pipe는 닫지 않는다
			execute_child(blackhole, child_util.pipe_i);
		}
		else // 부모
		{
			if (child_util.pipe_i == blackhole->pipe_cnt)
				child_util.last_child_pid = pid;
			close(child_util.pipefd[1]);
			if (child_util.pipe_i != 0) // 첫번째 block이 아닌 경우에는 저장해둔 prev_pipe삭제
				close(child_util.prev_pipe);
			if (child_util.pipe_i != blackhole->pipe_cnt)
				child_util.prev_pipe = dup(child_util.pipefd[0]);
			close(child_util.pipefd[0]);
			child_util.pipe_i++;
		}
	}
	set_terminal(1); // 시그널 입력 시 제어문자 표시
	signal(SIGINT, ignore_signal); // 자식에서는 SIGINT 넣으면 종료되고 부모에서는 개행만 발생
	pid = 0;
	while (pid != -1) // 실행시킨 자식 수 만큼만 wait하기
	{
		pid = waitpid(-1, &status, 0);
		if (child_util.last_child_pid != -1 && pid == child_util.last_child_pid)
			child_util.last_child_status = status;
		
	}
	ft_handle_last_status(child_util.last_child_status, blackhole);
}

static void	ft_handle_last_status(int last_status, t_blackhole *blackhole)
{
	int	status_signal;

	status_signal = last_status&0x7f;
	if (status_signal == 0)
		blackhole->exit_code = (last_status >> 8) & 0x000000ff;
	else if (status_signal != 0x7f)
	{
		if (status_signal == 3)
			write(2,"Quit: 3\n",8);
		blackhole->exit_code = (status_signal + 128);
	}
}

static void	execute_child(t_blackhole *blackhole, int pipe_i)
{
	const int	cmd_type = check_cmd_type(blackhole->parsed_input[pipe_i].cmd_list->head);
	int			exit_code;

	if (cmd_type <= 6)
	{
		execute_builtin(blackhole, cmd_type);
		exit(EXIT_SUCCESS); //TODO exit코드 처리
	}
	else
	{
		execute_nbuiltin(blackhole->parsed_input[pipe_i].cmd_list, blackhole->env_list);
		exit(EXIT_SUCCESS);
	}
}