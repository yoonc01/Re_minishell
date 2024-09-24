/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngho <youngho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:39:07 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/24 23:10:14 by youngho          ###   ########.fr       */
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
				close(prev_pipe);
			if (pipe_idx != pipecnt)
				prev_pipe = dup(pipefd[0]);
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
// echo -> path없다 -> 
// if ( execve )
	// excute 동작

static void set_pipe(int pipe_i, int pipe_cnt, int prev_pipe, int *pipefd)
{
	close(pipefd[0]);
	if (pipe_i != 0)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (pipe_i != pipe_cnt)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
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


