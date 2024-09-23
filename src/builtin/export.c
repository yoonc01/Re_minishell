/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:47:34 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/23 18:29:53 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_arg(t_env_list *env_list)
{
	t_env_node	*current_node;

	current_node = env_list->head;
	while (current_node != NULL)
	{
		write(STDIN_FILENO, current_node->env_key, ft_strlen(current_node->env_key));
		if (my_strcmp(current_node->env_value, ""))
		{
			write(STDIN_FILENO, "=", 1);
			write(STDIN_FILENO, current_node->env_value, ft_strlen(current_node->env_value));
		}
		write(STDIN_FILENO, "\n", 1);
		current_node = current_node->next;
	}
	return (1);
}

int	ft_export(t_inner_block_list *cmd_list, t_env_list *env_list)
{
	t_inner_block	*current_node;

	current_node = cmd_list->head->next;
	if (current_node == NULL)
		return (no_arg(env_list));
	while (current_node != NULL)
	{
		if (add_env(current_node->str, env_list) == 0)
			builtin_error("export : not an identifier: ", current_node->str);
		current_node = current_node->next;
	}
}
