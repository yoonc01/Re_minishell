/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:39:07 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/22 14:49:02 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void make_child(int pipecnt, t_block *parsed_input, t_env_list *env_list)
{
	int pipe_idx;

	pipe_idx = 0;
	while (pipe_idx <= pipecnt)
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
		ft_fork();
		pipe_idx++;
	}

}