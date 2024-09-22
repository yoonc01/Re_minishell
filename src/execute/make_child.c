/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:39:07 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/22 22:07:43 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pipe(int pipe_i, int pie_cnt, int prev_pipe, int *pipefd);
static void	apply_redir(t_inner_block_list *redirect_list);
static int	redirect_input(t_inner_block *redirect_block);
static int	redirect_output(t_inner_block *redirect_block);
static void execute_command(t_env_list *env_list, t_inner_block_list *cmd_list);

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
	while (pipe_idx <= pipecnt)
	{
		// print_parsing(pipe_idx, parsed_input, env_list);
		pipe(pipefd); // TODO 마지막 자식은 pipe 만들지 말지 정하기
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
			if (pipe_idx != 0 && prev_pipe >= 0)
				close(prev_pipe);
			prev_pipe = dup(pipefd[0]);
			close(pipefd[0]);
		}
		pipe_idx++;
	}
	pipe_idx = 0;
	while (pipe_idx < pipecnt)
	{
		wait(NULL);
		pipe_idx++;
	}

}

static void set_pipe(int pipe_i, int pie_cnt, int prev_pipe, int *pipefd)
{
	close(pipefd[0]);
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
			if (flag <= 1)
				dup2(redirect_input(curr_redirection), STDIN_FILENO);
			else
				dup2(redirect_output(curr_redirection), STDOUT_FILENO);
		}
		else
			flag = curr_redirection->type;
		curr_redirection = curr_redirection->next;
	}
}

static int redirect_input(t_inner_block *redirect_block)
{
	int	fd;
	int	open_flag;

	if (redirect_block->type == REDIR_IN)
		fd = open(redirect_block->str, O_RDONLY, 0);
	else
	{
		// TODO tmp파일 생성 후 heredoc 입력 받고 fd 리턴하기
		// heredoc 시 생성되는 tmp.txt 언제 삭제시킬지
	}
	if (fd < 0)
	{
		// TODO 파일 오픈 에러 처리
	}
	return (0);
}

static int redirect_output(t_inner_block *redirect_block)
{
	// TODO output 리다이렉션
	return (0);
}

static void execute_command(t_env_list *env_list, t_inner_block_list *cmd_list)
{
	t_inner_block	*cur_cmd = cmd_list->head;

	// while (cur_cmd)
	// {
	// 	printf("%s \n", cur_cmd->str);
	// 	cur_cmd = cur_cmd->next;
	// }
	
	printf("\n");
	exit(1);
}
