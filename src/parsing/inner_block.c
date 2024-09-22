/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:09:27 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/21 14:27:22 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_inner_block_list	*create_inner_block_list(void)
{
	t_inner_block_list	*inner_block_list;

	inner_block_list = (t_inner_block_list *)malloc(sizeof(t_inner_block_list));
	if (inner_block_list == NULL)
		malloc_fail();
	inner_block_list->head = NULL;
	inner_block_list->size = 0;
	return (inner_block_list);
}

// 파싱한 inner_block를 해당하는 block멤버에 맞게 연결리스트 맨 뒤의 멤버로 넣어줌
void add_inner_block(t_inner_block_list *lst, t_inner_block *new_node)
{
	t_inner_block	*current_node;
	
	if (lst->head == NULL)
		lst->head = new_node;
	else
	{
		current_node = lst->head;
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new_node;
	}
}

void	free_inner_block(t_inner_block_list *lst)
{
	t_inner_block	*temp_inner_block;
	t_inner_block	*current_inner_block;

	current_inner_block = lst->head;
	while (current_inner_block != NULL)
	{
		temp_inner_block = current_inner_block->next;
		free(current_inner_block->str);
		free(current_inner_block);
		current_inner_block = temp_inner_block;
	}
	free(lst);
}
