/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:39:07 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/22 17:50:10 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void set_pipe(int pipe_i, int pie_cnt, int prev_pipe, int *pipefd);
static void apply_redir(t_inner_block_list redirect_list);

void make_child(int pipecnt, t_block *parsed_input, t_env_list *env_list)
{
	int pipe_idx;
	int pid;
	int pipefd[2];
	int prev_pipe;

	pipe_idx = 0;
	while (pipe_idx <= pipecnt)
	{
		print_parsing(pipe_idx, parsed_input, env_list);
		pipe(pipefd);
		pid = fork();
		if (pid < 0)
			exit(1);
		else if (!pid) //자식
		{
			set_pipe(pipe_idx, pipecnt, prev_pipe, pipefd); // 파이프와 연결되게 stdin stdout 설정
			apply_redir(*(parsed_input[pipe_idx].redirection_list));
			execute_command(pipe_idx, pipecnt, env_list, parsed_input);
		}
		else // 부모
		{
			close(pipefd[1]);
			if (pipe_idx != 0)
				close(prev_pipe);
			prev_pipe = dup(pipefd[0]);
			close(pipefd[0]);
		}
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

static void apply_redir(t_inner_block_list redirect_list)
{
	int	input_fd;
	int	output_fd;
	int	flag;
	t_inner_block *curr_redirection;

	flag = 0;
	curr_redirection = redirect_list.head;
	while(curr_redirection)
	{
		if (my_strcmp(curr_redirection->str, "<<") == 0)
			flag = 0;
		else if (my_strcmp(curr_redirection->str, "<") == 0)
			flag = 1;
		else if (my_strcmp(curr_redirection->str, ">>") == 0)
			flag = 2;
		else if (my_strcmp(curr_redirection->str, ">") == 0)
			flag = 3;
		else
		{
			if (flag <= 1)
				dup2(redirect_input(flag), STDIN_FILENO);
			else
				dup2(redirect_output(flag), STDOUT_FILENO);
		}
		curr_redirection = curr_redirection->next;
	}
}

static int get_redirect_flag(char *str, )

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

