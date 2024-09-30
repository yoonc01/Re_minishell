/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:47:46 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/30 20:21:38 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_no_new_line(const char *str)
{
	int	idx;

	if (str[0] == '-' && str[1] == 'n')
	{
		idx = 2;
		while (str[idx] != '\0')
		{
			if (str[idx] != 'n')
				return (0);
			str++;
		}
		return (1);
	}
	return (0);
}

int	ft_echo(t_blackhole *blackhole)
{
	char			*str;
	int				new_line;
	int				is_option;
	t_inner_block	*current_node;

	current_node = blackhole->parsed_input->cmd_list->head->next;
	new_line = 1;
	is_option = 1;
	while (current_node != NULL)
	{
		str = current_node->str;
		if (is_option && check_no_new_line(str))
			new_line = 0;
		else
		{
			write(STDOUT_FILENO, str, ft_strlen(str));
			if (current_node->next != NULL)
				write(STDOUT_FILENO, " ", 1);
			is_option = 0;
		}
		current_node = current_node->next;
	}
	write(STDOUT_FILENO, "\n", new_line);
	return (EXIT_SUCCESS);
}
