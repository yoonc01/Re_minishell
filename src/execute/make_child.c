/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:39:07 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/23 15:24:47 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pipe(int pipe_i, int pie_cnt, int prev_pipe, int *pipefd);
static void	apply_redir(t_inner_block_list *redirect_list);
static void	redirect_input(t_inner_block *redirect_block, int flag);
static void	redirect_output(t_inner_block *redirect_block, int flag);

void print_parsing(int pipe_idx, t_block *parsed_input, t_env_list *env_list)
{
		t_inner_block_list *cmd_list = parsed_input[pipe_idx].cmd_list;
		t_inner_block_list *redirection_list = parsed_input[pipe_idx].redirection_list;
		t_inner_block *temp = cmd_list->head;
		while (temp != NULL)
		{
			printf("%s\n", temp->str);
			temp = temp->next;
		}
		temp = redirection_list->head;
		while (temp != NULL)
		{
			printf("%s\n", temp->str);
			temp = temp->next;
		}
		printf("\n");
}


void make_child(int pipecnt, t_block *parsed_input, t_env_list *env_list)
{
	int pipe_idx;
	int pid;
	int pipefd[2];
	int prev_pipe;

	pipe_idx = 0;
	prev_pipe = -1;
	// export 구조체에 환경변수
	while (pipe_idx <= pipecnt)
	{
		pipe(pipefd);
		pid = fork();
		if (pid < 0)
			exit(1); // TODO
		else if (pid == 0) //자식
		{
			set_pipe(pipe_idx, pipecnt, prev_pipe, pipefd);
			apply_redir(parsed_input[pipe_idx].redirection_list);
			execute_command(env_list, parsed_input[pipe_idx].cmd_list);
		}
		else // 부모
		{
			close(pipefd[1]);
			if (pipe_idx != 0) // 첫번째 block이 아닌 경우에는 저장해둔 prev_pipe삭제
			{
				close(prev_pipe);
				if (pipe_idx != pipecnt)
					prev_pipe = dup(pipefd[0]);
			}
			close(pipefd[0]);
		}
		pipe_idx++;
	}
	pipe_idx = 0;
	while (pipe_idx <= pipecnt)
	{
		wait(NULL);
		pipe_idx++;
	}
}

// 자식프로세스 - 파이프에 유무, excute로 해야하는가?

// in & out 처리 (pipe가 있는 경우 파이프 생성)
// if ( builtin )
	// builtin 동작

// path를 추출
// PATH라는 환경변수 자체가 있냐 없냐
// echo -> pathㄱ ㅏ없다 -> 
// if ( execve )
	// excute 동작

static void set_pipe(int pipe_i, int pipe_cnt, int prev_pipe, int *pipefd)
{
	close(pipefd[0]);
	if (pipe_i != pipe_cnt)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	if (pipe_i != 0)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
}

static void apply_redir(t_inner_block_list *redirect_list)
{
	int	flag;
	t_inner_block *curr_redirection;

	flag = 0;
	curr_redirection = redirect_list->head;
	while(curr_redirection)
	{
		if (curr_redirection->type == WORD)
		{
			if (flag <= 3)
				redirect_input(curr_redirection, flag);
			else
				redirect_output(curr_redirection, flag);
		}
		else
			flag = curr_redirection->type;
		curr_redirection = curr_redirection->next;
	}
}

static void redirect_input(t_inner_block *redirect_block, int flag)
{
	int	fd;

	if (flag == REDIR_IN)
	{
		fd = open(redirect_block->str, O_RDONLY, 0);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else // HEREDOC
	{
		// TODO tmp파일 생성 후 heredoc 입력 받고 fd 리턴하기
		// heredoc 시 생성되는 tmp.txt 언제 삭제시킬지
	}
	if (fd < 0)
	{
		// TODO 파일 오픈 에러 처리
	}
}

static void redirect_output(t_inner_block *redirect_block, int flag)
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


