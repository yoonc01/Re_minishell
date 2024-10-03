/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:47:34 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/03 11:37:28 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_arg(t_env_list *env_list)
{
	t_env_node	*current_node;

	current_node = env_list->head;
	while (current_node != NULL)
	{
		write(STDOUT_FILENO, current_node->env_key,
			ft_strlen(current_node->env_key));
		if (my_strcmp(current_node->env_value, ""))
		{
			write(STDOUT_FILENO, "=", 1);
			write(STDOUT_FILENO, current_node->env_value,
				ft_strlen(current_node->env_value));
		}
		write(STDOUT_FILENO, "\n", 1);
		current_node = current_node->next;
	}
	return (EXIT_SUCCESS);
}

int	ft_export(t_blackhole *blackhole)
{
	t_inner_block	*current_node;

	current_node = blackhole->parsed_input->cmd_list->head->next;
	if (current_node == NULL)
		return (no_arg(blackhole->env_list));
	while (current_node != NULL)
	{
		if (add_env(current_node->str, blackhole->env_list) == 0)
		{
			builtin_error2("minishell: ",
				current_node->str, ": export : not a valid identifier");
			return (EXIT_FAILURE);
		}
		current_node = current_node->next;
	}
	return (EXIT_SUCCESS);
}
