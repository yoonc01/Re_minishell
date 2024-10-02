/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngho <youngho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 00:09:12 by youngho           #+#    #+#             */
/*   Updated: 2024/10/02 15:00:23 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_exit(char *field1, char *field2)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, field1, ft_strlen(field1));
	if (field2)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, field2, ft_strlen(field2));
	}
	write(STDERR_FILENO, "\n", 1);
}
