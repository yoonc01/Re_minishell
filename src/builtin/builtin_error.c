/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:28:40 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/23 18:32:25 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//TEST 필요
int	builtin_error(char *str, char *token)
{
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, token, ft_strlen(token));
	write(STDERR_FILENO, "\n", 1);
}