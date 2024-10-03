/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:48:56 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/03 17:32:50 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	put_block_cmd(t_deque *tokens, int block_i, t_blackhole *blackhole)
{
	t_inner_block_list	*cmd_list;
	t_inner_block		*new_node;
	char				*cmd;

	cmd_list = blackhole->parsed_input[block_i].cmd_list;
	cmd = process(tokens->front->str, blackhole, 0);
	if (cmd == NULL)
		return (0);
	if ((my_strcmp(cmd, "") == 0 && ft_strchr(tokens->front->str, '$')))
	{
		delete_front(tokens);
		free(cmd);
		return (1);
	}
	new_node = (t_inner_block *)malloc(sizeof(t_inner_block));
	if (new_node == NULL)
		malloc_fail();
	new_node->str = cmd;
	new_node->type = tokens->front->token_type;
	new_node->next = NULL;
	add_inner_block(cmd_list, new_node);
	delete_front(tokens);
	return (1);
}

static int	put_block_redirect(t_deque *tokens,
		int block_i, t_blackhole *blackhole)
{
	t_inner_block_list	*redirection_list;
	t_inner_block		*new_node_redirection;
	t_inner_block		*new_node_file;

	redirection_list = blackhole->parsed_input[block_i].redirection_list;
	if (tokens->front->next == NULL || tokens->front->next->token_type != WORD)
		return (parsing_error(tokens, blackhole));
	new_node_redirection = (t_inner_block *)malloc(sizeof(t_inner_block));
	if (new_node_redirection == NULL)
		malloc_fail();
	new_node_file = (t_inner_block *)malloc(sizeof(t_inner_block));
	if (new_node_file == NULL)
		malloc_fail();
	new_node_redirection->str = ft_strdup(tokens->front->str);
	new_node_redirection->type = tokens->front->token_type;
	new_node_redirection->next = new_node_file;
	new_node_file->str = process(tokens->front->next->str,
			blackhole, tokens->front->token_type == HEREDOC);
	new_node_file->next = NULL;
	new_node_file->type = tokens->front->next->token_type;
	delete_front(tokens);
	delete_front(tokens);
	add_inner_block(redirection_list, new_node_redirection);
	return (1);
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
		free_invalid(blackhole->parsed_input, tokens, block_i);
	else
		blackhole->exit_code = 0;
}

void	parsing(char *input, t_blackhole *blackhole)
{
	t_deque	*tokens;

	blackhole->pipe_cnt = 0;
	tokens = tokenize(input, &blackhole->pipe_cnt);
	if (tokens == NULL)
	{
		parsing_error(tokens, blackhole);
		return ;
	}
	parsing_block(tokens, blackhole);
	free(tokens);
}
