/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:37:25 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/22 16:37:19 by hyoyoon          ###   ########.fr       */
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
	t_env_node	*prev_node;
	t_env_node	*current_node;

	if (env_list->head != NULL && my_strcmp(env_list->head->env_key, str) == 0)
	{
		current_node = env_list->head;
		env_list->head = env_list->head->next;
		free_env_node(current_node);
		env_list->size = env_list->size - 1;
	}
	current_node = env_list->head;
	while (current_node != NULL && my_strcmp(current_node->env_key, str) != 0)
	{
		prev_node = current_node;
		current_node = current_node->next;
	}
	if (current_node == NULL)
		return ;
	prev_node->next = current_node->next;
	free_env_node(current_node);
	env_list->size = env_list->size - 1;
}

void	ft_unset(char	*env_key, t_env_list *env_list)
{
	delete_env_node(env_key, env_list);
}