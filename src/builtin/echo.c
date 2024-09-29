/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:47:46 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/29 13:03:23 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// option -nnnnnnnnn -----nn possible...
int	ft_echo(t_blackhole *blackhole)
{
	int				new_line;
	t_inner_block	*current_node;

	current_node = blackhole->parsed_input->cmd_list->head->next;
	new_line = !(my_strcmp(current_node->str, "-n") == 0);
	while (current_node != NULL)
	{
		write(STDOUT_FILENO, current_node->str, ft_strlen(current_node->str));
		if (current_node->next != NULL)
			write(STDOUT_FILENO, " ", 1);
		else
			write(STDERR_FILENO, "\n", new_line);
		current_node = current_node->next;
	}
	return (EXIT_SUCCESS);
}