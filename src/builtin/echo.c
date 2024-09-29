/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycho2 <ycho2@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:47:46 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/29 21:27:48 by ycho2            ###   ########.fr       */
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
			write(STDERR_FILENO, "\n", new_line); // FIX 리다이렉션 시 해당 코드로인해 개행 출력
		current_node = current_node->next;
	}
	return (EXIT_SUCCESS);
}