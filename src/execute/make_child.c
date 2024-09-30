/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:39:07 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/30 12:35:15 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child(t_blackhole *blackhole, int pipe_i);

// void print_parsing(int pipe_idx, t_block *parsed_input, t_env_list *env_list)
// {
// 		t_inner_block_list *cmd_list = parsed_input[pipe_idx].cmd_list;
// 		t_inner_block_list *redirection_list = parsed_input[pipe_idx].redirection_list;
// 		t_inner_block *temp = cmd_list->head;
// 		while (temp != NULL)
// 		{
// 			printf("%s\n", temp->str);
// 			temp = temp->next;
// 		}
// 		temp = redirection_list->head;
// 		while (temp != NULL)
// 		{
// 			printf("%s\n", temp->str);
// 			temp = temp->next;
// 		}
// 		printf("\n");
// }


void make_child(t_blackhole *blackhole)
{
	int	pid;
	int *childfd;
	t_pipe_util pipe_util;
	int	heredoc_sigint;

	pipe_util.pipe_i = 0;
	pipe_util.pipecnt = blackhole->pipe_cnt;
	pipe_util.prev_pipe = -1;
	// export 구조체에 환경변수
	while (pipe_util.pipe_i <= blackhole->pipe_cnt)
	{
		pipe(pipe_util.pipefd);
		pipe_util.childfd[0] = STDIN_FILENO;
		pipe_util.childfd[1] = STDOUT_FILENO;
		heredoc_sigint = set_child_redir(blackhole->parsed_input[pipe_util.pipe_i].redirection_list, &pipe_util);
		if (heredoc_sigint == 1)
			break;
		signal(SIGQUIT, ignore_signal); // 자식에서execve실행하면 시그널 핸들러 초기화된다
		pid = fork();
		if (pid < 0)
			exit(1); // TODO
		else if (pid == 0) //자식
		{
			close(pipe_util.pipefd[0]); // 부모가 pipefd 들고 있으므로 close해도 된다
			dup2(pipe_util.childfd[0], STDIN_FILENO);
			dup2(pipe_util.childfd[1], STDOUT_FILENO);
			close(pipe_util.pipefd[1]); // 리다이렉션 끝났으니까 닫아도 된다
			// 아직 이전 자식의 출력이 끝나지 않았을 수 있으므로 prev_pipe는 닫지 않는다
			execute_child(blackhole, pipe_util.pipe_i);
		}
		else // 부모
		{
			close(pipe_util.pipefd[1]);
			if (pipe_util.pipe_i != 0) // 첫번째 block이 아닌 경우에는 저장해둔 prev_pipe삭제
				close(pipe_util.prev_pipe);
			if (pipe_util.pipe_i != blackhole->pipe_cnt)
				pipe_util.prev_pipe = dup(pipe_util.pipefd[0]);
			close(pipe_util.pipefd[0]);
			pipe_util.pipe_i++;
		}
	}
	set_terminal(1); // 시그널 입력 시 제어문자 표시
	signal(SIGINT, ignore_signal); // 자식에서는 SIGINT 넣으면 종료되고 부모에서는 개행만 발생
	while (pipe_util.pipe_i > 0)
	{
		wait(NULL);
		pipe_util.pipe_i--;
	}
}

// 자식프로세스 - 파이프에 유무, excute로 해야하는가?

// in & out 처리 (pipe가 있는 경우 파이프 생성)
// if ( builtin )
	// builtin 동작

// path를 추출
// PATH라는 환경변수 자체가 있냐 없냐
// echo -> path없다 -> 
// if ( execve )
	// excute 동작

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