/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoyoon <hyoyoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:33:25 by hyoyoon           #+#    #+#             */
/*   Updated: 2024/09/23 15:40:36 by hyoyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_inner_block_list *cmd_list)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
    if (cwd != NULL)
	{
		write(STDIN_FILENO, cwd, ft_strlen(cwd));
        free(cwd);
    }
	else
		malloc_fail();
    return (1);	
}