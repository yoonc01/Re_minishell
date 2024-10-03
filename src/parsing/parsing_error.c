/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:21:39 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/03 12:52:26 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_error(char *type)
{
	write(STDERR_FILENO, "minishell: syntax error near unexpected token `", 47);
	write(STDERR_FILENO, type, ft_strlen(type));
	write(STDERR_FILENO, "`\n", 2);
}

int	parsing_error(t_deque *tokens, t_blackhole *blackhole)
{
	if (tokens->front->next == NULL)
		write_error("newline");
	else if (tokens->front->next != WORD)
		write_error(tokens->front->next->str);
	blackhole->exit_code = 258;
	return (0);
}
