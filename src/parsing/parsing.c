/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:48:56 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/02 16:20:30 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	put_block_cmd(t_deque *tokens, int block_i, t_blackhole *blackhole)
{
	t_inner_block_list	*cmd_list;
	t_inner_block		*new_node;
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
	new_node_file = (t_inner_block *)malloc(sizeof(t_inner_block));
	new_node_redirection->str = ft_strdup(tokens->front->str);
	new_node_redirection->type = tokens->front->token_type;
	new_node_redirection->next = new_node_file;
	new_node_file->str = rm_quote_ap_env(tokens->front->next->str,
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
		return ;
	parsing_block(tokens, blackhole);
	free(tokens);
}
