/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 16:48:56 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/09 19:00:58 by ycho2            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_block	*parsing_block(t_deque *tokens, int pipecnt)
{
	t_block	*parsed_input;
	int		block_i;
	int		grammar_valid;

	parsed_input = (t_block *)malloc(sizeof(t_block) * (pipecnt + 1));
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
		}
		else
			grammar_valid = put_block_redirect(tokens, parsed_input[block_i]);
	}
}

int	parsing(char *input)
{
	t_deque	*tokens;
	int		pipecnt;

	pipecnt = 0;
	tokens = tokenize(input, &pipecnt);
	if (tokens == 0)
		return (0);
}
