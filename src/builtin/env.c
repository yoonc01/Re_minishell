/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:27:00 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/23 15:11:07 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env_list *env_list)
{
	t_env_node	*current_node;

	current_node = env_list->head;
	while (current_node != NULL)
	{
		if (my_strcmp(current_node->env_value, ""))
		{
			write(STDIN_FILENO, current_node->env_key, ft_strlen(current_node->env_key));
			write(STDIN_FILENO, "=", 1);
			write(STDIN_FILENO, current_node->env_value, ft_strlen(current_node->env_value));
			write(STDIN_FILENO, "\n", 1);
		}
		current_node = current_node->next;
	}
	return (1);
}

char	*get_env(char *key, t_env_list *env_list)
{
	t_env_node	*current_node;

	current_node = env_list->head;
	while (current_node != NULL)
	{
		if (my_strcmp(current_node->env_key, key) == 0)
			return (ft_strdup(current_node->env_value));
		current_node = current_node->next;
	}
	return (NULL);
}
