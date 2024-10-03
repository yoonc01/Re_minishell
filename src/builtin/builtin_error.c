/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:28:40 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/10/03 11:25:11 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_error(char *str, char *token)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	if (token != NULL)
		write(STDERR_FILENO, token, ft_strlen(token));
	write(STDERR_FILENO, "\n", 1);
}

void	builtin_error2(char *str, char *token, char *str2)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, token, ft_strlen(token));
	write(STDERR_FILENO, str2, ft_strlen(str2));
	write(STDERR_FILENO, "\n", 1);
}
