/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inner_block.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:09:27 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/30 20:03:25 by hyoyoon          ###   ########.fr       */
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

void	add_inner_block(t_inner_block_list *lst, t_inner_block *new_node)
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
	lst->size++;
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
