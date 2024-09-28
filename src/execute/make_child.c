/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngho <youngho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:39:07 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/29 02:04:25 by youngho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_child(t_env_list *env_list, t_inner_block_list *cmd_list);

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


void make_child(int pipecnt, t_block *parsed_input, t_env_list *env_list)
{
	int	pid;
	int *childfd;
	t_pipe_util pipe_util;

	pipe_util.pipe_i = 0;
	pipe_util.pipecnt = pipecnt;
	pipe_util.prev_pipe = -1;
	
	// export 구조체에 환경변수
	while (pipe_util.pipe_i <= pipecnt)
	{
		pipe(pipe_util.pipefd);
		pipe_util.childfd[0] = STDIN_FILENO;
		pipe_util.childfd[1] = STDOUT_FILENO;
		set_child_redir(parsed_input[pipe_util.pipe_i].redirection_list, &pipe_util);
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
			execute_child(env_list, parsed_input[pipe_util.pipe_i].cmd_list);
		}
		else // 부모
		{
			close(pipe_util.pipefd[1]);
			if (pipe_util.pipe_i != 0) // 첫번째 block이 아닌 경우에는 저장해둔 prev_pipe삭제
				close(pipe_util.prev_pipe);
			if (pipe_util.pipe_i != pipecnt)
				pipe_util.prev_pipe = dup(pipe_util.pipefd[0]);
			close(pipe_util.pipefd[0]);
		}
		pipe_util.pipe_i++;
	}
	pipe_util.pipe_i = 0;
	while (pipe_util.pipe_i <= pipecnt)
	{
		wait(NULL);
		pipe_util.pipe_i++;
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

static void	execute_child(t_env_list *env_list, t_inner_block_list *cmd_list)
{
	const int	cmd_type = check_cmd_type(cmd_list->head);
	int			exit_code;

	if (cmd_type <= 6)
	{
		exit_code = execute_builtin(cmd_list, env_list, cmd_type);
		exit(1); //TODO exit코드 처리
	}
	else
	{
		execute_nbuiltin(cmd_list, env_list);
		exit(1);
	}
}