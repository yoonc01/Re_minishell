/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:48:56 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/11 19:28:26 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_inner_block(t_inner_block **lst, t_inner_block *new_node)
{
	t_inner_block	*current_node;
	
	if (*lst == NULL)
		*lst = new_node;
	else
	{
		current_node = *lst;
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new_node;
	}
}
int	put_block_cmd(t_deque *tokens, t_block parsed_input)
{
	t_inner_block	*new_node;
	t_inner_block	*current_node;
	t_inner_block	**cmd_list;

	cmd_list = parsed_input.cmd_list;
	new_node = (t_inner_block *)malloc(sizeof(t_inner_block));
	new_node->str = ft_strdup(tokens->front->str);
	new_node->next = NULL;
	add_inner_block(cmd_list, new_node);
	delete_front(tokens);
	return (1);
}

int	put_block_redirection(t_deque *tokens, t_block parsed_input)
//TODO error 시 누수 확인 
{
	t_inner_block	*new_node_redirection;
	t_inner_block	*new_node_file;
	t_inner_block	*current_node;
	t_inner_block	**redirection_list;

	redirection_list = parsed_input.redirection_list;
	if (tokens->front->next == NULL || tokens->front->next->token_type != WORD)
		return (0);
	new_node_redirection = (t_inner_block *)malloc(sizeof(t_inner_block));
	new_node_file = (t_inner_block *)malloc(sizeof(t_inner_block));
	new_node_redirection->str = ft_strdup(tokens->front->str);
	new_node_redirection->next = new_node_file;
	delete_front(tokens);
	new_node_file->str = ft_strdup(tokens->front->str);
	new_node_file->next = NULL;
	delete_front(tokens);
	add_inner_block(redirection_list, new_node_redirection);
	return (1);
}

t_block	*parsing_block(t_deque *tokens, int pipecnt)
{
	t_block	*parsed_input;
	int		block_i;
	int		grammar_valid;

	parsed_input = (t_block *)ft_calloc((pipecnt + 1), sizeof(t_block));
	block_i = 0;
	while(block_i < pipecnt + 1)
	{
		parsed_input[block_i].cmd_list = (t_inner_block **)calloc(1, sizeof(t_inner_block *));
		parsed_input[block_i].redirection_list = (t_inner_block **)calloc(1, sizeof(t_inner_block *));
		block_i++;
	}
	block_i = 0;
	grammar_valid = 1;
	while (tokens->front != NULL && grammar_valid)
	{
		if (tokens->front->token_type == WORD)
			grammar_valid = put_block_cmd(tokens, parsed_input[block_i]);
		else if (tokens->front->token_type == PIPE)
		{
			if (tokens->front->next == NULL)
				grammar_valid = 0;
			block_i++;
			delete_front(tokens);
		}
		else
			grammar_valid = put_block_redirect(tokens, parsed_input[block_i]);
	}
	if (grammar_valid == 0)
		free_parsed_input(parsed_input, tokens, block_i);
	return (parsed_input);
}

t_block	*parsing(char *input)
{
	t_deque	*tokens;
	int		pipecnt;
	t_block	*parsed_input;

	pipecnt = 0;
	tokens = tokenize(input, &pipecnt);
	if (tokens == NULL)
		return (0);
	parsed_input = parsing_block(tokens, pipecnt);
	return (parsed_input);
	
}
