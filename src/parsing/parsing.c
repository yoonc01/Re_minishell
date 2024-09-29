/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:48:56 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/29 14:22:44 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 토큰화한 WORD가 cmd일경우 여기로 들어온다
// 환경변수가 들어있을경우 적용해서 파싱한다
static int	put_block_cmd(t_deque *tokens, int block_i, t_blackhole *blackhole)
{
	t_inner_block_list	*cmd_list;
	t_inner_block		*new_node;
	t_inner_block		*current_node;
	char				*cmd;

	cmd_list = blackhole->parsed_input[block_i].cmd_list;
	new_node = (t_inner_block *)malloc(sizeof(t_inner_block));
	cmd = rm_quote_ap_env(tokens->front->str, blackhole, 0);
	new_node->str = cmd;
	new_node->type = tokens->front->token_type;
	new_node->next = NULL;
	add_inner_block(cmd_list, new_node);
	delete_front(tokens);
	return (1);
}

// 현재 파싱중인 block 의 redirection멤버에 데이터 넣어줌
static int	put_block_redirect(t_deque *tokens, int block_i, t_blackhole *blackhole)
{
	t_inner_block_list	*redirection_list;
	t_inner_block		*new_node_redirection;
	t_inner_block		*new_node_file;
	t_inner_block		*current_node;

	redirection_list = blackhole->parsed_input[block_i].redirection_list;
	if (tokens->front->next == NULL || tokens->front->next->token_type != WORD)
		return (parsing_error(tokens, blackhole));
	new_node_redirection = (t_inner_block *)malloc(sizeof(t_inner_block));
	new_node_file = (t_inner_block *)malloc(sizeof(t_inner_block));
	new_node_redirection->str = ft_strdup(tokens->front->str);
	new_node_redirection->type = tokens->front->token_type;
	new_node_redirection->next = new_node_file;
	new_node_file->str = rm_quote_ap_env(tokens->front->next->str, blackhole, tokens->front->token_type == HEREDOC);
	new_node_file->next = NULL;
	new_node_file->type = tokens->front->next->token_type;
	delete_front(tokens);
	delete_front(tokens);
	add_inner_block(redirection_list, new_node_redirection);
	return (1);
}


static void	free_invalid_grammer(t_block *parsed_input, t_deque *tokens, int block_i)
{
	int					idx;
	t_inner_block_list *cmd_list;
	t_inner_block_list *redirection_list;

	idx = 0;
	while (idx <= block_i)
	{
		cmd_list = parsed_input[idx].cmd_list;
		redirection_list = parsed_input[idx].redirection_list;
		free_inner_block(cmd_list);
		free_inner_block(redirection_list);
		idx++;
	}
	free(parsed_input);
	while (tokens->front != NULL)
		delete_front(tokens);
}

static void	init_parsed_input(t_blackhole *blackhole)
{
	int		block_i;
	int		pipe_cnt;
	t_block	*parsed_input;

	block_i = 0;
	pipe_cnt = blackhole->pipe_cnt;
	parsed_input = (t_block *)ft_calloc(pipe_cnt + 1, sizeof(t_block));
	while (block_i < pipe_cnt + 1)
	{
		parsed_input[block_i].cmd_list = create_inner_block_list();
		parsed_input[block_i].redirection_list = create_inner_block_list();
		block_i++;
	}
	blackhole->parsed_input = parsed_input;
}

// 파이프 마다 블록 만든 뒤 블록 리스트로 만들어서 parsed_input에 넣어준다 
static void	parsing_block(t_deque *tokens, t_blackhole *blackhole)
{
	int		block_i;
	int		grammer_valid;

	init_parsed_input(blackhole);
	block_i = 0;
	grammer_valid = 1;
	while (tokens->front != NULL && grammer_valid)
	{
		if (tokens->front->token_type == WORD)
			grammer_valid = put_block_cmd(tokens, block_i, blackhole);
		else if (tokens->front->token_type == PIPE)
		{
			if (tokens->front->next == NULL)
				grammer_valid = parsing_error(tokens, blackhole);
			block_i++;
			delete_front(tokens);
		}
		else
			grammer_valid = put_block_redirect(tokens, block_i, blackhole);
	}
	if (!grammer_valid)
		free_invalid_grammer(blackhole->parsed_input, tokens, block_i);
	else
		blackhole->exit_code = 0;
}

void	parsing(char *input, t_blackhole *blackhole)
{
	t_deque	*tokens;

	blackhole->pipe_cnt = 0;
	tokens = tokenize(input, &blackhole->pipe_cnt);
	if (tokens == NULL)
		return ;
	parsing_block(tokens, blackhole);
	free(tokens);
}
