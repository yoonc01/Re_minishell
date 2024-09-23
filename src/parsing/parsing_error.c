/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:21:39 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/23 17:38:58 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	write_error(char *type)
{
	write(STDERR_FILENO, "minishell: syntex error near unexpected token `", 47);
	write(STDERR_FILENO, type, ft_strlen(type));
	write(STDERR_FILENO, "`\n", 2);
	return (0);
}


int	parsing_error(t_deque *tokens)
{
	if (tokens->front->next == NULL)
		return (write_error("newline"));
	else if (tokens->front->next != WORD)
		return (write_error(tokens->front->next->str));
}