/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:37:25 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/22 15:51:57 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_node(t_env_node *node)
{
	free(node->env_key);
	free(node->env_value);
	free(node);
}

void	delete_env_node(char *str, t_env_list *env_list)
{
	t_env_node	*current_node;
	t_env_node	*temp;

	if (env_list->head != NULL && my_strcmp(env_list->head->env_key, str) == 0)
	{
		temp = env_list->head;
		env_list->head = env_list->head->next;
		free_env_node(temp);
		env_list->size = env_list->size - 1;
		return ;
	}
	current_node = env_list->head;
	while (current_node != NULL && current_node->next != NULL)
	{
		if (my_strcmp(current_node->next->env_key, str) == 0)
		{
			temp = current_node->next;
			current_node->next = temp->next;
			free_env_node(temp);
			env_list->size = env_list->size - 1;
			return ;
		}
		current_node = current_node->next;
	}
}
void	unset(char	*env_key, t_env_list *env_list)
{
	delete_env_node(env_key, env_list);
}
