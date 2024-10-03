/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 00:09:12 by youngho           #+#    #+#             */
/*   Updated: 2024/10/03 13:27:27 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	err_exit(char *field1, char *field2, int return_value)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, field1, ft_strlen(field1));
	if (field2)
	{
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, field2, ft_strlen(field2));
	}
	write(STDERR_FILENO, "\n", 1);
	return (return_value);
}
