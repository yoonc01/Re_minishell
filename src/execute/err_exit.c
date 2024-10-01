/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youngho <youngho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 00:09:12 by youngho           #+#    #+#             */
/*   Updated: 2024/10/01 00:38:33 by youngho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	err_exit(char *field1, char *field2)
{
	write(2, "minishell: ", 11);
	write(2, field1, ft_strlen(field1));
	if (field2)
	{
		write(2, ": ", 2);
		write(2, field2, ft_strlen(field2));
	}
	write(2,"\n",1);
}