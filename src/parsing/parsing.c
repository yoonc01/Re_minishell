/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:48:56 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/23 17:56:40 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 토큰화한 WORD가 cmd일경우 여기로 들어온다
// 환경변수가 들어있을경우 적용해서 파싱한다
int	put_block_cmd(t_deque *tokens, t_block parsed_input, t_env_list *env_list)
{
	t_inner_block_list	*cmd_list;
	t_inner_block		*new_node;
	t_inner_block		*current_node;
	char				*cmd;

	cmd_list = parsed_input.cmd_list;
	new_node = (t_inner_block *)malloc(sizeof(t_inner_block));
	cmd = rm_quote_ap_env(tokens->front->str, env_list, 0);
	new_node->str = cmd;
	new_node->type = tokens->front->token_type;
	new_node->next = NULL;
	add_inner_block(cmd_list, new_node);
	delete_front(tokens);
	return (1);
}

// 현재 파싱중인 block 의 redirection멤버에 데이터 넣어줌
int	put_block_redirect(t_deque *tokens, t_block current_block, t_env_list *env_list) // 받아오는 인자수정
//TODO error 시 누수 확인 
{
	t_inner_block_list	*redirection_list;
	t_inner_block		*new_node_redirection;
	t_inner_block		*new_node_file;
	t_inner_block		*current_node;
	int					is_heredoc;

	redirection_list = current_block.redirection_list;
	if (tokens->front->next == NULL || tokens->front->next->token_type != WORD)
		return (parsing_error(tokens));
	new_node_redirection = (t_inner_block *)malloc(sizeof(t_inner_block));
	new_node_file = (t_inner_block *)malloc(sizeof(t_inner_block));
	new_node_redirection->str = ft_strdup(tokens->front->str);
	new_node_redirection->type = tokens->front->token_type;
	new_node_redirection->next = new_node_file;
	new_node_file->str = rm_quote_ap_env(tokens->front->next->str, env_list, tokens->front->token_type == HEREDOC);
	new_node_file->next = NULL;
	delete_front(tokens);
	delete_front(tokens);
	add_inner_block(redirection_list, new_node_redirection);
	return (1);
}

t_block	*free_invalid_grammer(t_block *parsed_input, t_deque *tokens, int block_i)
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
	return (NULL);
}

// 파이프 마다 블록 만든 뒤 블록 리스트로 만들어서 parsed_input에 넣어준다 
t_block	*parsing_block(t_deque *tokens, int pipecnt, t_env_list *env_list)
{
	t_block	*parsed_input;
	int		block_i;
	int		grammar_valid;

	parsed_input = (t_block *)ft_calloc(pipecnt + 1, sizeof(t_block));
	block_i = 0;
	while(block_i < pipecnt + 1)
	{
		parsed_input[block_i].cmd_list = create_inner_block_list();
		parsed_input[block_i].redirection_list = create_inner_block_list();
		block_i++;
	}
	block_i = 0;
	grammar_valid = 1;
	while (tokens->front != NULL && grammar_valid)
	{
		if (tokens->front->token_type == WORD)
			grammar_valid = put_block_cmd(tokens, parsed_input[block_i], env_list);
		else if (tokens->front->token_type == PIPE)
		{
			if (tokens->front->next == NULL)
				grammar_valid = parsing_error(tokens);
			block_i++;
			delete_front(tokens);
		}
		else
			grammar_valid = put_block_redirect(tokens, parsed_input[block_i], env_list);
	}
	if (grammar_valid == 0)
		return(free_invalid_grammer(parsed_input, tokens, pipecnt));
	return (parsed_input);
}

t_block	*parsing(char *input, int *pipecnt, t_env_list *env_list)
{
	t_deque	*tokens;
	t_block	*parsed_input;

	*pipecnt = 0;
	tokens = tokenize(input, pipecnt);
	if (tokens == NULL)
		return (NULL);
	parsed_input = parsing_block(tokens, *pipecnt, env_list);
	free(tokens);
	return (parsed_input);
}
