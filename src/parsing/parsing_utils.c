/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 16:46:33 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/11 18:09:07 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_inner_block(t_inner_block **lst)
{
	t_inner_block	*temp_inner_block;

	while (*lst)
	{
		temp_inner_block = (*lst)->next;
		free((*lst));
		*lst = temp_inner_block;
	}
}
void	free_parsed_input(t_block *parsed_input, t_deque *tokens, int block_i)
{
	int				idx;
	t_inner_block	**cmd_list;
	t_inner_block	**redirection_list;

	idx = 0;
	while(idx <= block_i)
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