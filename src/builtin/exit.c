/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 15:33:28 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/28 17:04:58 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_alldigit(const char *str)
{
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

static int	my_atoi(const char *str)
{
	long	ans;
	int		sign;

	ans = 0;
	sign = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		ans = 10 * ans + (*str - '0');
		str++;
	}
	return ((int) sign * ans);
}

int	ft_exit(t_inner_block_list *cmd_list)
{
	int				exit_code;
	t_inner_block	*current_node;

	current_node = cmd_list->head->next;
	if (current_node != NULL)
	{
		if (!ft_alldigit(current_node->str))
		{
			builtin_error("exit: numeric argument required: ", current_node->str);
			exit(255);
		}
		if (current_node->next != NULL)
		{
			builtin_error("exit: too many arguments", NULL);
			return (EXIT_FAILURE);
		}
		exit_code = my_atoi(current_node->str) % 256;
		exit_code = (exit_code + 256) % 256;
		exit(exit_code);
	}
	exit(EXIT_SUCCESS);
}